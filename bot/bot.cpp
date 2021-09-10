/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "bot.h"

#include <QDir>
#include <QMetaEnum>

#include "entitymanager.h"
#include "eventhandler.h"
#include "util/globals.h"
#include "qml/mongodb.h"
#include "logging/logfactory.h"
#include "qml/sqldatabase.h"
#include "qml/sqlquery.h"
#include "qml/http.h"
#include "qml/mongofind.h"
#include "qml/mongoinsert.h"
#include "qml/enums/networkrequest.h"
#include "qml/httpmultipart.h"
#include "qml/httppart.h"


const QString Bot::BOT_IMPORT_IDENTIFIER = "BotApi";
const int Bot::BOT_API_MAJOR_VERSION = 1;
const int Bot::BOT_API_MINOR_VERSION = 0;
const QString Bot::BOT_TYPE_IDENTIFIER = "BotScript";
const QString Bot::FILE_OPEN_MODE_IDENTIFIER = "OpenMode";
const QString Bot::SQL_IDENTIFIER = "Sql";
const QString Bot::NETWORK_REQUEST_IDENTIFIER = "NetworkRequest";
const QString Bot::NO_CREATABLE_ENUM = "Cannot Instantiate Enums";

Bot::Bot() {
    qRegisterMetaType<QSharedPointer<TimedBinding> >();
    qRegisterMetaType<LogContext::LogLevel>();
    qRegisterMetaType<QSharedPointer<GatewayPayload> >();
    qRegisterMetaType<QSharedPointer<GuildEntity> >();
    qRegisterMetaType<QSharedPointer<Route> >();
    qRegisterMetaType<QSharedPointer<EventContext> >();
    qRegisterMetaType<QSharedPointer<CommandRestrictions> >();
    qRegisterMetaType<SqlDatabase>();
    qRegisterMetaType<MongoDB>();
    qRegisterMetaType<MongoFind>();
    qRegisterMetaType<MongoInsert>();
    qRegisterMetaType<SqlQuery>();
    qRegisterMetaType<SqlField>();
    qRegisterMetaType<SqlRecord>();
    qRegisterMetaType<SqlError>();
    qRegisterMetaType<File>();
    qRegisterMetaType<HttpPart>();
    qRegisterMetaType<HttpMultiPart>();
    qRegisterMetaType<CommandRestrictions::RestrictionState>();
    qmlRegisterType<BotScript>(BOT_IMPORT_IDENTIFIER.toUtf8(),
                               BOT_API_MAJOR_VERSION,
                               BOT_API_MINOR_VERSION,
                               BOT_TYPE_IDENTIFIER.toUtf8());

    qmlRegisterUncreatableType<OpenMode>(BOT_IMPORT_IDENTIFIER.toUtf8(),
                          BOT_API_MAJOR_VERSION,
                          BOT_API_MINOR_VERSION,
                          FILE_OPEN_MODE_IDENTIFIER.toUtf8(),
                          NO_CREATABLE_ENUM);

    qmlRegisterUncreatableType<Sql>(BOT_IMPORT_IDENTIFIER.toUtf8(),
                          BOT_API_MAJOR_VERSION,
                          BOT_API_MINOR_VERSION,
                          SQL_IDENTIFIER.toUtf8(),
                          NO_CREATABLE_ENUM);

    qmlRegisterUncreatableType<NetworkRequest>(BOT_IMPORT_IDENTIFIER.toUtf8(),
                          BOT_API_MAJOR_VERSION,
                          BOT_API_MINOR_VERSION,
                          NETWORK_REQUEST_IDENTIFIER.toUtf8(),
                          NO_CREATABLE_ENUM);
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

    connect(gateway, &Gateway::dispatchEvent, entityManager, &EntityManager::saveEvent);

    connect(gateway, &Gateway::guildOnline, entityManager, &EntityManager::saveEvent);

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
