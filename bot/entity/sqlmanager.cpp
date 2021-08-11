
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

#include "sqlmanager.h"

#include <QSqlError>

#include "util/enumutils.h"


const QString SqlManager::CONNECTION_NAME = "entityManager";
const QString SqlManager::COMMAND_RESTRICTIONS = "CommandRestrictions";
const QString SqlManager::SQL_CREATE_COMMAND_RESTRICTIONS_TABLE_SQLITE = QString("CREATE TABLE %1 (id integer PRIMARY KEY AUTOINCREMENT, guild_id varchar(256), command_name varchar(256), target_id varchar(256), state integer);").arg(COMMAND_RESTRICTIONS);
const QString SqlManager::SQL_CREATE_COMMAND_RESTRICTIONS_TABLE = QString("CREATE TABLE %1 (id integer PRIMARY KEY AUTO_INCREMENT, guild_id varchar(256), command_name varchar(256), target_id varchar(256), state integer);").arg(COMMAND_RESTRICTIONS);
const QString SqlManager::SQL_SELECT_COMMAND_RESTRICTION_ID = QString("SELECT COUNT(id) FROM %1 WHERE guild_id = ? AND target_id = ? AND command_name = ?;").arg(COMMAND_RESTRICTIONS);
const QString SqlManager::SQL_INSERT_COMMAND_RESTRICTION = QString("INSERT INTO %1 (guild_id, command_name, target_id, state) VALUES (?, ?, ?, ?);").arg(COMMAND_RESTRICTIONS);
const QString SqlManager::SQL_UPDATE_COMMAND_RESTRICTION = QString("UPDATE %1 SET state = ? WHERE guild_id = ? and command_name = ? AND target_id = ?;").arg(COMMAND_RESTRICTIONS);
const QString SqlManager::SQL_REMOVE_COMMAND_RESTRICTION = QString("DELETE FROM %1 WHERE guild_id = ? AND command_name = ?;").arg(COMMAND_RESTRICTIONS);
const QString SqlManager::SQL_REMOVE_COMMAND_RESTRICTION_FOR_ID = QString("DELETE FROM %1 WHERE guild_id = ? AND command_name = ? AND target_id = ?;").arg(COMMAND_RESTRICTIONS);
const QString SqlManager::SQL_SELECT_COMMAND_RESTRICTIONS_FOR_GUILD = QString("SELECT command_name, target_id, state FROM %1 WHERE guild_id = ?;").arg(COMMAND_RESTRICTIONS);


void
SqlManager::init() {
    _database = QSqlDatabase::addDatabase(_databaseContext.driverName, CONNECTION_NAME);

    _database.setDatabaseName(_databaseContext.databaseName);

    int type = EnumUtils::keyToValue<SettingsParam::Database::DatabaseType>(_databaseContext.driverName);

    QString query;

    if (type != SettingsParam::Database::QSQLITE) {
        _database.setHostName(_databaseContext.hostName);

        _database.setUserName(_databaseContext.userName);

        _database.setPassword(_databaseContext.password);

        _database.setPort(_databaseContext.port);

        query = SQL_CREATE_COMMAND_RESTRICTIONS_TABLE;
    } else {
        query = SQL_CREATE_COMMAND_RESTRICTIONS_TABLE_SQLITE;
    }

    if (isDbOpen()) {
        _logger->info("EntityManager successfully connected to database...");

        if (!_database.tables().contains(COMMAND_RESTRICTIONS, Qt::CaseInsensitive)) {

            _database.exec(query);

            if (_database.lastError().isValid()) {
                _logger->warning(_database.lastError().text());
            }
        }
    }
}

bool
SqlManager::isDbOpen() {
    if (!_database.open()) {
        _logger->warning(QString("EntityManager failed to open database... %1").arg(_database.lastError().text()));

        return false;
    }

    return true;
}

void
SqlManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {
    if (!isDbOpen()) {
        return;
    }

    QSqlQuery query(_database);

    QMap<QString, CommandRestrictions::RestrictionState> restrictionMap = restrictions->getRestrictions();

    for (auto commandName : restrictionMap.keys()) {
        query.prepare(SQL_SELECT_COMMAND_RESTRICTION_ID);

        query.bindValue(0, restrictions->getGuildId());

        query.bindValue(1, restrictions->getTargetId());

        query.bindValue(2, commandName);

        if (!query.exec()) {
            _logger->warning(query.lastError().databaseText());

            _logger->warning(_database.lastError().databaseText());

            return;
        } else {
            query.first();
        }

        int count = query.value(0).toInt();

        if (count > 0) {
            updateRestriction(restrictions->getGuildId(),
                              commandName,
                              restrictions->getTargetId(),
                              restrictionMap[commandName]);
        } else {
            insertRestriction(restrictions->getGuildId(),
                              commandName,
                              restrictions->getTargetId(),
                              restrictionMap[commandName]);
        }
    }
}

void
SqlManager::restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) {
    if (restrictions->getTargetId().isEmpty()) {
        clearCommand(restrictions);
    } else {
        clearCommandForId(restrictions);
    }
}

void
SqlManager::clearCommand(QSharedPointer<CommandRestrictions> restrictions) {
    QSqlQuery query(_database);

    QMap<QString, CommandRestrictions::RestrictionState> restrictionMap = restrictions->getRestrictions();

    for (auto commandName : restrictionMap.keys()) {
        query.prepare(SQL_REMOVE_COMMAND_RESTRICTION);

        query.bindValue(0, restrictions->getGuildId());

        query.bindValue(1, commandName);

        query.exec();

        if (query.lastError().isValid()) {
            _logger->warning(query.lastError().text());
        }
    }
}

void
SqlManager::clearCommandForId(QSharedPointer<CommandRestrictions> restrictions) {
    QSqlQuery query(_database);

    QMap<QString, CommandRestrictions::RestrictionState> restrictionMap = restrictions->getRestrictions();

    for (auto commandName : restrictionMap.keys()) {
        query.prepare(SQL_REMOVE_COMMAND_RESTRICTION_FOR_ID);

        query.bindValue(0, restrictions->getGuildId());

        query.bindValue(1, commandName);

        query.bindValue(2, restrictions->getTargetId());

        query.exec();

        if (query.lastError().isValid()) {
            _logger->warning(query.lastError().text());
        }
    }
}

void
SqlManager::insertRestriction(const QString &guildId,
                                 const QString &commandName,
                                 const QString &targetId,
                                 CommandRestrictions::RestrictionState state) {
    QSqlQuery query(_database);

    query.prepare(SQL_INSERT_COMMAND_RESTRICTION);

    query.bindValue(0, guildId);

    query.bindValue(1, commandName);

    query.bindValue(2, targetId);

    query.bindValue(3, state);

    query.exec();

    if (query.lastError().isValid()) {
        _logger->warning(query.lastError().text());
    }
}

void
SqlManager::updateRestriction(const QString &guildId,
                                 const QString &commandName,
                                 const QString &targetId,
                                 CommandRestrictions::RestrictionState state) {
    QSqlQuery query(_database);

    query.prepare(SQL_UPDATE_COMMAND_RESTRICTION);

    query.bindValue(0, state);

    query.bindValue(1, guildId);

    query.bindValue(2, commandName);

    query.bindValue(3, targetId);

    query.exec();

    if (query.lastError().isValid()) {
        _logger->warning(query.lastError().text());
    }
}

void
SqlManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {
    QSqlQuery query(_database);

    query.prepare(SQL_SELECT_COMMAND_RESTRICTIONS_FOR_GUILD);

    query.bindValue(0, guildEntity->getId());

    query.exec();

    if (query.lastError().isValid()) {
        _logger->warning(query.lastError().text());

        return;
    }

    QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> > mappedStateIdsByCommand;

    while (query.next()) {
        QString commandName = query.value(0).toString();

        QString targetId = query.value(1).toString();

        int state = query.value(2).toInt();

        mappedStateIdsByCommand[commandName][targetId] = CommandRestrictions::RestrictionState(state);
    }

    guildEntity->setMappedStateIdsByCommand(mappedStateIdsByCommand);
}
