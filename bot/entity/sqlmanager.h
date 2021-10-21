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

#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QObject>

#include "idbmanager.h"


class SqlManager : public IDBManager
{
    static const QString CONNECTION_NAME;
    static const QString SQL_CREATE_COMMAND_RESTRICTIONS_TABLE_SQLITE;
    static const QString SQL_CREATE_COMMAND_RESTRICTIONS_TABLE;
    static const QString SQL_SELECT_COMMAND_RESTRICTION_ID;
    static const QString SQL_INSERT_COMMAND_RESTRICTION;
    static const QString SQL_UPDATE_COMMAND_RESTRICTION;
    static const QString SQL_REMOVE_COMMAND_RESTRICTION;
    static const QString SQL_REMOVE_COMMAND_RESTRICTION_FOR_ID;
    static const QString SQL_SELECT_COMMAND_RESTRICTIONS_FOR_GUILD;

    QSqlDatabase _database;
    Logger *_logger = LogFactory::getLogger();

    bool isDbOpen();
    void insertRestriction(const QString &guildId,
                           const QString &commandName,
                           const QString &targetId,
                           CommandRestrictions::RestrictionState state);
    void updateRestriction(const QString &guildId,
                           const QString &commandName,
                           const QString &targetId,
                           CommandRestrictions::RestrictionState state);
    void clearCommand(QSharedPointer<CommandRestrictions> restrictions);
    void clearCommandForId(QSharedPointer<CommandRestrictions> restrictions);

public:

    SqlManager(DatabaseContext context) {
        _databaseContext = context;
    }

    void initGuild(QSharedPointer<GuildEntity> payload) override;
    void init() override;
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) override;
    void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) override;
    void saveEvent(QSharedPointer<GatewayPayload> payload) override {
        notImplemented("SqlManager saveEvent");
    }
};

#endif // ENTITYMANAGER_H
