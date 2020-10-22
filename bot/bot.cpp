#include "bot.h"

#include <QDir>
#include <QMetaEnum>

#include "entitymanager.h"
#include "eventhandler.h"
#include "util/globals.h"
#include "logging/logfactory.h"
#include "qml/sqldatabase.h"
#include "qml/sqlquery.h"


Bot::Bot() {
    qRegisterMetaType<QSharedPointer<TimedBinding> >();
    qRegisterMetaType<LogContext::LogLevel>();
    qRegisterMetaType<QSharedPointer<GatewayPayload> >();
    qRegisterMetaType<QSharedPointer<GuildEntity> >();
    qRegisterMetaType<QSharedPointer<Route> >();
    qRegisterMetaType<QSharedPointer<EventContext> >();
    qRegisterMetaType<QSharedPointer<CommandRestrictions> >();
    qRegisterMetaType<SqlDatabase>();
    qRegisterMetaType<SqlQuery>();
}

void
Bot::run(QSharedPointer<Settings> settings) {

    Gateway *gateway = new Gateway(settings);

    gateway->moveToThread(&_gatewayThread);

    connect(&_gatewayThread, &QThread::finished, gateway, &QObject::deleteLater);

    connect(&_gatewayThread, &QThread::started, gateway, &Gateway::init);

    EventHandler *eventHandler = new EventHandler(settings);

    _scriptBuilder = new ScriptBuilder(eventHandler, settings);

    eventHandler->moveToThread(&_eventHandlerThread);

    EntityManager *entityManager = new EntityManager(settings);

    entityManager->moveToThread(&_entityManagerThread);

    connect(&_eventHandlerThread, &QThread::finished, eventHandler, &QObject::deleteLater);

    connect(&_eventHandlerThread, &QThread::started, eventHandler, &EventHandler::init);

    connect(_scriptBuilder, &ScriptBuilder::guildReady, eventHandler, &EventHandler::guildReady);

    connect(gateway, &Gateway::dispatchEvent, eventHandler, &EventHandler::processEvent);

    connect(gateway, &Gateway::guildOnline, entityManager, &EntityManager::initGuildFromPayload);

    connect(gateway, &Gateway::defaultGuildOnline, entityManager, &EntityManager::initGuild);

    connect(eventHandler, &EventHandler::reloadScripts, _scriptBuilder, &ScriptBuilder::buildScripts);

    connect(entityManager, &EntityManager::guildInitialized, _scriptBuilder, &ScriptBuilder::buildScripts);

    connect(&_entityManagerThread, &QThread::started, entityManager, &EntityManager::init);

    _eventHandlerThread.start();

    _entityManagerThread.start();

    _gatewayThread.start();

    _gatewayThread.setPriority(QThread::HighestPriority);
}
