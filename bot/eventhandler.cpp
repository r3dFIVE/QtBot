#include "eventhandler.h"

#include "globals.h"
#include "payloads/hello.h"

#include <QJsonDocument>

EventHandler::EventHandler(QObject *parent) :
QObject(parent)
{
}

void
EventHandler::processEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    switch (payload->op) {
        case GatewayEvents::DISPATCH:
            //Receive	dispatches an event
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
