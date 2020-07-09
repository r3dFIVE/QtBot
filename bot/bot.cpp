#include "bot.h"
#include "eventhandler.h"
#include "util/globals.h"
#include "logging/logfactory.h"

#include <QDir>
#include <QMetaEnum>


Bot::Bot()
{
    qRegisterMetaType<QSharedPointer<JsonSerializable> >();
    qRegisterMetaType<QSharedPointer<GatewayPayload::GatewayPayload> >();
    qRegisterMetaType<LogContext::LogLevel>();
    qRegisterMetaType<QSharedPointer<CommandRegistrar> >();
}

void
Bot::loadRegistrar() {
    emit registrarReady(_factory->buildRegistrar(*this));
}


void
Bot::run(QSharedPointer<Settings> settings) {

    QString botToken = settings->value(SettingsParam::Connection::BOT_TOKEN).toString();
    QString scriptDir = settings->value(SettingsParam::Script::SCRIPT_DIRECTORY).toString();

    _factory = new RegistrarFactory(botToken, scriptDir);

    Gateway *connection = new Gateway(settings);
    connection->moveToThread(&_gatewayThread);
    connect(&_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);
    connect(&_gatewayThread, &QThread::started, connection, &Gateway::init);

    EventHandler *eventHandler = new EventHandler(settings);

    eventHandler->moveToThread(&_eventHandlerThread);
    connect(&_eventHandlerThread, &QThread::finished, eventHandler, &QObject::deleteLater);
    connect(&_eventHandlerThread, &QThread::started, eventHandler, &EventHandler::init);
    connect(&_eventHandlerThread, &QThread::started, this, &Bot::loadRegistrar);
    connect(this, &Bot::registrarReady, eventHandler, &EventHandler::processRegistrar);
    connect(connection, &Gateway::dispatchEvent, eventHandler, &EventHandler::processEvent);

    _eventHandlerThread.start();
    _gatewayThread.start();
    _gatewayThread.setPriority(QThread::HighestPriority);
}
