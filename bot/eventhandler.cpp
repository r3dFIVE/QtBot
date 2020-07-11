#include "eventhandler.h"
#include "util/corecommand.h"
#include "util/globals.h"
#include "qml/botscript.h"
#include "payloads/message.h"

#include <QJsonDocument>
#include <QMetaEnum>
#include <QDebug>
#include <QMap>
#include <QSqlDatabase>
#include <QtSql>


EventHandler::EventHandler(QSharedPointer<Settings> settings) {
    _settings = settings;
}


void
EventHandler::init() {

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
EventHandler::processDispatch(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    QMetaEnum metaEnum = QMetaEnum::fromType<GatewayEvents::Events>();
    int enumValue = metaEnum.keyToValue(payload->t.toUtf8());

    switch(enumValue) {
        //TODO parse message type
        case GatewayEvents::MESSAGE_CREATE:
            processMessageCreate(payload);
            break;
        default:
            return;
    }
}

void
EventHandler::processMessageCreate(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    QSharedPointer<EventContext> context = QSharedPointer<EventContext>(new EventContext(payload->d));

    QString command = parseCommandToken(context->content.toString());

    ICommand::CommandMapping mapping = _scriptRegistrar->getCommand(command);

    if (!mapping.first.isEmpty()) {
        mapping.second->execute(mapping.first.toUtf8(), context);
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

void
EventHandler::processRegistrar(QSharedPointer<CommandRegistrar> registrar) {
    _scriptRegistrar = registrar;
}
