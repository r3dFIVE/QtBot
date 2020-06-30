#include "eventhandler.h"
#include "util/function.h"
#include "util/globals.h"

#include <QJsonDocument>
#include <QMetaEnum>
#include <QDebug>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

EventHandler::EventHandler(QSharedPointer<Settings> settings)
{


    const auto addCommand = [this](auto name, auto lambda) {
        commands.insert(name, lambda);
    };

    addCommand(QString(".quote"), [&](const QString &args) -> void {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(settings->value(SettingsParam::Database::DATABASE_HOST).toString());
        db.setDatabaseName("quotes");
        db.setUserName(settings->value(SettingsParam::Database::DATABASE_USER).toString());
        db.setPassword(settings->value(SettingsParam::Database::DATABASE_PASSWORD).toString());
        db.setPort(settings->value(SettingsParam::Database::DATABASE_PORT).toInt());
        if (!db.open()) {
            qDebug() << db.lastError();
        }

        QList<QString> arguments = args.simplified().split(" ");
        QSqlQuery query;
        if (arguments.size() == 1) {
            query.prepare("SELECT quote,date,author FROM quotes.quote ORDER BY RAND() LIMIT 1");
        } else {
            query.prepare("SELECT quote,date,author FROM quotes.quote WHERE quote LIKE ?");
            query.bindValue(0, "%" + arguments.at(1) + "%");
        }
        query.exec();
        qDebug() << query.lastQuery();
        qDebug() << query.size();
        qDebug() << query.boundValue(0);
        while (query.next()) {
            qDebug() << "Quote:" << query.value(0) << " -- Date: "
                     << query.value(1) << " -- Author: " << query.value(2);
        }
    });
}

QString
EventHandler::parseCommandToken(QString message) {
    int start = -1;
    int i;
    for (i = 0; i < message.size(); i++) {
        if (start < 0 && message[i].isSpace()) {
            continue;
        } else if (start < 0 && !message[i].isSpace()) {
            start = i;
        } else if (start >= 0 && message[i].isSpace()) {
            break;
        }
    }    

    if (start >= 0) {
        return message.mid(start, i - start);
    } else {
        return QString();
    }
}


void
EventHandler::execute(QSharedPointer<GatewayPayload::GatewayPayload> payload) {

}

void
EventHandler::processDispatch(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    QMetaEnum metaEnum = QMetaEnum::fromType<GatewayEvents::Events>();
    int enumValue = metaEnum.keyToValue(payload->t.toUtf8());
    QString message = payload->d["content"].toString();
    QString command;
    switch(enumValue) {
    case GatewayEvents::MESSAGE_CREATE: {
        command = parseCommandToken(message);
        break;
    default:
        return;
    }
    }

    if (commands.contains(command)) {
        auto cmd = commands[command];
        cmd(message);
    }

}

void
EventHandler::processEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    switch (payload->op) {
        case GatewayEvents::DISPATCH:
            processDispatch(payload);
            break;
        case GatewayEvents::HEARTBEAT:
            //Send/Receive	used for ping checking
            break;
        case GatewayEvents::IDENTIFY:
            //Send	used for client handshake
            break;
        case GatewayEvents::STATUS_UPDATE:
            //Send	used to update the client status
            break;
        case GatewayEvents::VOICE_STATUS_UPDATE:
            //Send	used to join/move/leave voice channels
            break;
        case GatewayEvents::RESUME:
            //Send	used to resume a closed connection
            break;
        case GatewayEvents::RECONNECT:
            //Receive	used to tell clients to reconnect to the gateway
            break;
        case GatewayEvents::REQUEST_GUILD_MEMBERS:
            //Send	used to request guild members
            break;
        case GatewayEvents::INVALID_SESSION:
            //Receive	used to notify client they have an invalid session id
            break;
        case GatewayEvents::HEARTBEAT_ACK:
            //Receive	sent immediately following a client heartbeat that was received
            break;
    }
}
