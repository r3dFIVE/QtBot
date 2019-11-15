#include "bot.h"
#include "messagehandler.h"


Bot::Bot()
{
    qRegisterMetaType<GatewayPayload>();
}


void
Bot::run() {
    qDebug() << "in bot run.";


    GatewayConnection *connection = new GatewayConnection(QUrl(QStringLiteral("ws://192.168.1.72:1234")), nullptr);
    connection->moveToThread(&_gatewayThread);
    connect(&_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);
    connect(&_gatewayThread, &QThread::started, connection, &GatewayConnection::init);

    MessageHandler *messageHandler = new MessageHandler;
    messageHandler->moveToThread(&_messageHandlerThread);
    connect(connection, &GatewayConnection::payloadReady, messageHandler, &MessageHandler::processPayload);
    connect(messageHandler, &MessageHandler::updateHeartbeat, connection, &GatewayConnection::updateHeartbeatInterval);

    _messageHandlerThread.start();
    _gatewayThread.start();

    qDebug() << "in bot run. (finished)";
}
