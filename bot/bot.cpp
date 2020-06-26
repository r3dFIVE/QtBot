#include "bot.h"
#include "eventhandler.h"
#include "globals.h"
#include "logging/logfactory.h"

#include <QDir>
#include <QMetaEnum>


Bot::Bot()
{   
    qRegisterMetaType<QSharedPointer<JsonSerializable>>();
    qRegisterMetaType<QSharedPointer<GatewayPayload::GatewayPayload>>();
    qRegisterMetaType<LogContext::LogLevel>();
}

void
Bot::run(QSharedPointer<Settings> settings) {
    Gateway *connection = new Gateway(settings);
    connection->moveToThread(&_gatewayThread);
    connect(&_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);
    connect(&_gatewayThread, &QThread::started, connection, &Gateway::init);

    EventHandler *messageHandler = new EventHandler;
    messageHandler->moveToThread(&_messageServiceThread);
    connect(&_messageServiceThread, &QThread::finished, messageHandler, &QObject::deleteLater);
    connect(connection, &Gateway::dispatchEvent, messageHandler, &EventHandler::processEvent);

    _messageServiceThread.start();
    _gatewayThread.start();
    _gatewayThread.setPriority(QThread::HighestPriority);
}
