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

#include "entitymanager.h"

#include <QSqlError>
#include <QTimer>
#include <QDir>

#include "entity/mongomanager.h"


EntityManager::EntityManager() {
    clearFileCache();

    _databaseContext.init();
}

void
EntityManager::initGuildFromPayload(QSharedPointer<GatewayPayload> payload) {
    Guild jsonGuild(payload->getD());

    QSharedPointer<GuildEntity> guildEntity = QSharedPointer<GuildEntity>(new GuildEntity(jsonGuild));

    Guild guild(payload->getD());

    guildEntity->setId(guild.getId().toString());

    initGuild(guildEntity);
}

/*
 * Perform DB init when thread has started.
 */
void
EntityManager::init() {
    switch (_databaseContext.type) {
        case DatabaseType::QMONGODB:
            _manager = QSharedPointer<MongoManager>(new MongoManager(_databaseContext, this));
            break;
        case DatabaseType::QSQLITE:
        case DatabaseType::QMYSQL:
            _manager = QSharedPointer<SqlManager>(new SqlManager(_databaseContext, this));
            break;            
    }    

    _manager->init();
}


void
EntityManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {
    _manager->restrictionsUpdate(restrictions);
}

void
EntityManager::clearFileCache() {
    QDir tempDir(Settings::tempDirectory());

    _logger->trace(QString("Cleaning temporary file cache located at: %1")
                   .arg(Settings::tempDirectory()));

    tempDir.removeRecursively();
}

void
EntityManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {
    _manager->initGuild(guildEntity);

    QObject::connect(guildEntity.data(), &GuildEntity::restrictionsUpdate, this, &EntityManager::restrictionsUpdate);

    emit guildInitialized(guildEntity, false);
}

void
EntityManager::saveEvent(GatewayEvent::Event event, QSharedPointer<GatewayPayload> payload) {
    Q_UNUSED(event);

    _manager->saveEvent(payload);
}
