#include "eventhandler.h"

#include "globals.h"
#include "payloads/hello.h"

#include <QJsonDocument>

EventHandler::EventHandler(QObject *parent) :
QObject(parent)
{
}

void
EventHandler::processEvent(QSharedPointer<GatewayPayload> payload) {
    switch (payload->op) {
        case GatewayOpcodes::DISPATCH:
            //Receive	dispatches an event
            break;
        case GatewayOpcodes::HEARTBEAT:
            //Send/Receive	used for ping checking
            break;
        case GatewayOpcodes::IDENTIFY:
            //Send	used for client handshake
            break;
        case GatewayOpcodes::STATUS_UPDATE:
            //Send	used to update the client status
            break;
        case GatewayOpcodes::VOICE_STATUS_UPDATE:
            //Send	used to join/move/leave voice channels
            break;
        case GatewayOpcodes::RESUME:
            //Send	used to resume a closed connection
            break;
        case GatewayOpcodes::RECONNECT:
            //Receive	used to tell clients to reconnect to the gateway
            break;
        case GatewayOpcodes::REQUEST_GUILD_MEMBERS:
            //Send	used to request guild members
            break;
        case GatewayOpcodes::INVALID_SESSION:
            //Receive	used to notify client they have an invalid session id
            break;
        case GatewayOpcodes::HEARTBEAT_ACK:
            //Receive	sent immediately following a client heartbeat that was received
            break;
    }
}