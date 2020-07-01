#include "databasedriver.h"
#include "util/globals.h"

#include <QRandomGenerator>


DatabaseDriver::DatabaseDriver(QSharedPointer<Settings> settings)
{    
    _httpClient = QSharedPointer<HttpClient>(new HttpClient(settings));
    _logger = LogFactory::getLogger();
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName(settings->value(SettingsParam::Database::DATABASE_HOST).toString());
    _db.setDatabaseName("quotes");
    _db.setUserName(settings->value(SettingsParam::Database::DATABASE_USER).toString());
    _db.setPassword(settings->value(SettingsParam::Database::DATABASE_PASSWORD).toString());
    _db.setPort(settings->value(SettingsParam::Database::DATABASE_PORT).toInt());
}


void
DatabaseDriver::getQuote(const Message &message) {
    if (!_db.open()) {
        _logger->debug(_db.lastError().text());
        return;
    }

    QString args = message.getContent().toString();

    QList<QString> arguments = args.simplified().split(" ");

    _query = QSqlQuery(_db);

    if (arguments.size() == 1) {
        _query.prepare("SELECT quote,date,author FROM quotes.quote ORDER BY RAND() LIMIT 1");
    } else {
        QString clause = arguments.at(1);

        for (int i = 2; i < arguments.size(); ++i) {
            clause += QString (" %1").arg(arguments.at(i));
        }

        _query.prepare("SELECT quote,date,author FROM quotes.quote WHERE quote LIKE ?");
        _query.bindValue(0, QString("%%1%").arg(clause));
    }

    _query.exec();

    if (_query.size() > 1) {
        QRandomGenerator generator;

        generator.seed(QDateTime().currentMSecsSinceEpoch());

        int randomIndex = generator.bounded(_query.size() - 1);

        _query.seek(randomIndex);

        postQuery(message);

        logQuery();

    } else if (_query.next()) {
        postQuery(message);

        logQuery();

    } else {
        _logger->debug("No quote(s) found...");
    }
}

void
DatabaseDriver::nextQuote(const Message &message) {
    if (_query.size() <= 0) {
        _logger->debug("No quote(s) found...");
        return;
    } else if (_query.size() >= 2) {
        if (!_query.next()) {
            _query.seek(0);
        }
    }
    postQuery(message);
    logQuery();
}


void
DatabaseDriver::logQuery() {
    QString quoteNumber = QString("Quote [%1/%2]: ").arg(_query.at() + 1).arg(_query.size());
    QString logString =
            quoteNumber + _query.value(0).toString()
            + " -- Date: " + _query.value(1).toString()
            + " -- Author: " + _query.value(2).toString();
    _logger->debug(logString);
}

void
DatabaseDriver::postQuery(const Message &message) {
    QString quoteNumber = QString("Quote [%1/%2]: ").arg(_query.at() + 1).arg(_query.size());
    QString logString =
            quoteNumber + _query.value(0).toString()
            + " -- Date: " + _query.value(1).toString()
            + " -- Author: " + _query.value(2).toString();
    _httpClient->post(message, logString);
}
