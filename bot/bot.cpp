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
#include <QThreadPool>

#include "entitymanager.h"
#include "eventhandler.h"
#include "botjob/scriptmanager.h"
#include "logging/logfactory.h"
#include "qml/enums/htmltag.h"
#include "payloads/embed.h"
#include "payloads/embedfield.h"
#include "qml/mongodb.h"
#include "qml/sqldatabase.h"
#include "qml/sqlquery.h"
#include "qml/http.h"
#include "qml/mongofindoptions.h"
#include "qml/mongoinsertoptions.h"
#include "qml/enums/networkrequest.h"
#include "qml/httpmultipart.h"
#include "qml/httppart.h"
#include "qml/httpresponse.h"
#include "qml/tempfile.h"
#include "qml/domattribute.h"
#include "qml/domparser.h"
#include "qml/domnode.h"

#include <logging/logworker.h>


const QString Bot::BOT_IMPORT_IDENTIFIER = "BotApi";
const int Bot::BOT_API_MAJOR_VERSION = 1;
const int Bot::BOT_API_MINOR_VERSION = 0;
const QString Bot::BOT_TYPE_IDENTIFIER = "BotScript";
const QString Bot::FILE_OPEN_MODE_IDENTIFIER = "OpenMode";
const QString Bot::HTML_TAG_TYPE_IDENTIFIER = "HtmlTag";
const QString Bot::SQL_IDENTIFIER = "Sql";
const QString Bot::NETWORK_REQUEST_IDENTIFIER = "NetworkRequest";
const QString Bot::NO_CREATABLE_ENUM = "Cannot Instantiate Enums";
const QString Bot::GOODBYE = "Shutting down, have nice day! Beep Boop.";

Bot::Bot() {
    qRegisterMetaType<QSharedPointer<TimedBinding> >();
    qRegisterMetaType<Logger::LogLevel>();
    qRegisterMetaType<QSharedPointer<GatewayPayload> >();
    qRegisterMetaType<QSharedPointer<GuildEntity> >();
    qRegisterMetaType<QSharedPointer<Route> >();
    qRegisterMetaType<QSharedPointer<EventContext> >();
    qRegisterMetaType<QSharedPointer<CommandRestrictions> >();
    qRegisterMetaType<MongoFindOptions>();
    qRegisterMetaType<MongoInsertOptions*>();
    qRegisterMetaType<SqlQuery>();
    qRegisterMetaType<SqlError*>();
    qRegisterMetaType<DOMParser*>();
    qRegisterMetaType<DOMNode*>();
    qRegisterMetaType<DOMAttribute*>();
    qRegisterMetaType<File*>();
    qRegisterMetaType<HttpPart>();
    qRegisterMetaType<HttpMultiPart>();
    qRegisterMetaType<HttpResponse*>();
    qRegisterMetaType<QSharedPointer<TempFile>>();
    qRegisterMetaType<CommandRestrictions::RestrictionState>();
    qRegisterMetaType<GatewayEvent::Event>();
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

    qmlRegisterUncreatableType<HtmlTag>(BOT_IMPORT_IDENTIFIER.toUtf8(),
                          BOT_API_MAJOR_VERSION,
                          BOT_API_MINOR_VERSION,
                          HTML_TAG_TYPE_IDENTIFIER.toUtf8(),
                          NO_CREATABLE_ENUM);
}

Bot::~Bot() {
    _logger->trace("Attemping graceful shutdown...");

    _logger->trace("Shutting down Gateway thread...");

    _gatewayThread.quit();

    _gatewayThread.wait();

    _logger->trace("Shutting down Entity Manager thread...");

    _entityManagerThread.quit();

    _entityManagerThread.wait();

    while (QThreadPool::globalInstance()->activeThreadCount()) {
        _logger->trace(QString("Waiting on %1 Bot Scripts to finish...")
                       .arg(QThreadPool::globalInstance()->activeThreadCount()));

        QThreadPool::globalInstance()->waitForDone(250);

        qApp->processEvents();
    }

    _logger->trace("Shutting down Gateway thread...");

    _eventHandlerThread.quit();

    _eventHandlerThread.wait();

    _logger->trace("Freeing loaded BotScripts...");

    delete _scriptManager;

    _logger->trace("Shutting down logging thread...");

    _loggingThread.quit();

    _loggingThread.wait();

    LogFactory::cleanup();

    qDebug().noquote() << "Goodbye...";
}

void
Bot::run() {
    LogWorker *logWorker = new LogWorker();

    LogFactory::init(logWorker);

    logWorker->moveToThread(&_loggingThread);

    _logger = LogFactory::getLogger(this);

    connect(&_loggingThread, &QThread::finished, logWorker, &QObject::deleteLater);

    Gateway *gateway = new Gateway();

    gateway->moveToThread(&_gatewayThread);

    connect(&_gatewayThread, &QThread::finished, gateway, &QObject::deleteLater);

    connect(&_gatewayThread, &QThread::started, gateway, &Gateway::init);

    EventHandler *eventHandler = new EventHandler();

    _scriptManager = new ScriptManager(eventHandler);

    eventHandler->moveToThread(&_eventHandlerThread);

    connect(&_eventHandlerThread, &QThread::finished, eventHandler, &QObject::deleteLater);

    connect(&_eventHandlerThread, &QThread::started, eventHandler, &EventHandler::init);

    connect(_scriptManager, &ScriptManager::guildReady, eventHandler, &EventHandler::guildReady);

    connect(gateway, &Gateway::dispatchEvent, eventHandler, &EventHandler::processEvent);

    connect(eventHandler, &EventHandler::reloadScripts, _scriptManager, &ScriptManager::buildScripts);

    EntityManager *entityManager = new EntityManager();

    entityManager->moveToThread(&_entityManagerThread);

    connect(gateway, &Gateway::dispatchEvent, entityManager, &EntityManager::saveEvent);

    connect(gateway, &Gateway::guildOnline, entityManager, &EntityManager::initGuildFromPayload);

    connect(gateway, &Gateway::defaultGuildOnline, entityManager, &EntityManager::initGuild);

    connect(entityManager, &EntityManager::guildInitialized, _scriptManager, &ScriptManager::buildScripts);

    connect(&_entityManagerThread, &QThread::started, entityManager, &EntityManager::init);

    connect(&_entityManagerThread, &QThread::finished, entityManager, &QObject::deleteLater);

    _loggingThread.start();

    _eventHandlerThread.start();

    _entityManagerThread.start();

    _gatewayThread.start();

    _gatewayThread.setPriority(QThread::HighestPriority);
}
