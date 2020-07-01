#ifndef DATABASEDRIVER_H
#define DATABASEDRIVER_H

#include "util/settings.h"
#include "logging/logfactory.h"
#include "payloads/message.h"
#include "httpclient.h"

#include <QObject>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class DatabaseDriver : public QObject
{
    Q_OBJECT

    Logger *_logger;
    QSqlDatabase _db;
    QSqlQuery _query;
    QSharedPointer<HttpClient> _httpClient;

    void logQuery();
    void postQuery(const Message &message);

public:
    DatabaseDriver(QSharedPointer<Settings> settings);

    void getQuote(const Message &message);
    void nextQuote(const Message &message);

};

#endif // DATABASEDRIVER_H
