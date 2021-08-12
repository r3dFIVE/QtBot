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

#include "entity/mongomanager.h"
#include "util/enumutils.h"


void
EntityManager::initGuildFromPayload(QSharedPointer<GatewayPayload> payload) {
    Guild jsonGuild(payload->getD());

    QSharedPointer<GuildEntity> guildEntity = QSharedPointer<GuildEntity>(new GuildEntity(jsonGuild));

    Guild guild(payload->getD());

    guildEntity->setId(guild.getId().toString());

    QObject::connect(guildEntity.data(), &GuildEntity::restrictionsRemoval, this, &EntityManager::restrictionsRemoval);

    QObject::connect(guildEntity.data(), &GuildEntity::restrictionsUpdate, this, &EntityManager::restrictionsUpdate);

    initGuild(guildEntity);
}

/*
 * Perform DB init when thread has started.
 */
void
EntityManager::init() {
    switch (_databaseContext.type) {
        case SettingsParam::Database::QMONGODB:
            _manager = QSharedPointer<MongoManager>(new MongoManager(_databaseContext));
            break;
        case SettingsParam::Database::QSQLITE:
        case SettingsParam::Database::QMYSQL:
            _manager = QSharedPointer<SqlManager>(new SqlManager(_databaseContext));
            break;            
    }

    _manager->init();
}


void
EntityManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {
    _manager->restrictionsUpdate(restrictions);
}

void
EntityManager::restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) {
    _manager->restrictionsRemoval(restrictions);
}

void
EntityManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {
    _manager->initGuild(guildEntity);

    emit guildInitialized(guildEntity);
}

void
EntityManager::saveEvent(QSharedPointer<GatewayPayload> payload) {
    _manager->saveEvent(payload);
}
