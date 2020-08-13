#include "bot.h"
#include "entitymanager.h"
#include "eventhandler.h"
#include "util/globals.h"
#include "logging/logfactory.h"

#include <QDir>
#include <QMetaEnum>

Bot::Bot() {
    qRegisterMetaType<QSharedPointer<GatewayPayload> >();
    qRegisterMetaType<QSharedPointer<JsonSerializable> >();
    qRegisterMetaType<QSharedPointer<Route> >();
    qRegisterMetaType<QSharedPointer<GuildEntity> >();
    qRegisterMetaType<LogContext::LogLevel>();
}

Bot::~Bot() {
    delete _factory;
}

void
Bot::loadCommands(QSharedPointer<GuildEntity> guild) {
    emit guildReady(_factory->buildCommands(guild));
}

void
Bot::reloadAllCommands() {
    emit reloadAllAvailableGuilds();
}

void
Bot::run(QSharedPointer<Settings> settings) {
    _factory = new ScriptBuilder(this, settings);

    Gateway *connection = new Gateway(settings);

    connection->moveToThread(&_gatewayThread);

    connect(&_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);

    connect(&_gatewayThread, &QThread::started, connection, &Gateway::init);

    EventHandler *eventHandler = new EventHandler;

    eventHandler->moveToThread(&_eventHandlerThread);

    EntityManager *entityManager = new EntityManager;

    entityManager->moveToThread(&_entityManagerThread);

    connect(&_eventHandlerThread, &QThread::finished, eventHandler, &QObject::deleteLater);

    connect(this, &Bot::guildReady, eventHandler, &EventHandler::guildReady);

    connect(connection, &Gateway::dispatchEvent, eventHandler, &EventHandler::processEvent);

    connect(eventHandler, &EventHandler::guildOnline, entityManager, &EntityManager::initGuild);

    connect(eventHandler, &EventHandler::reloadCommands, this, &Bot::loadCommands);

    connect(entityManager, &EntityManager::guildInitialized, this, &Bot::loadCommands);

    connect(this, &Bot::reloadAllAvailableGuilds, eventHandler, &EventHandler::reloadAllAvailableGuilds);

    _eventHandlerThread.start();

    _gatewayThread.start();

    _entityManagerThread.start();

    _gatewayThread.setPriority(QThread::HighestPriority);
}
