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

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>
#include <QSharedPointer>

#include "entity/guildentity.h"
#include "entity/sqlmanager.h"
#include "payloads/guild.h"
#include "payloads/gatewaypayload.h"


class EntityManager : public QObject
{
    Q_OBJECT

    QSharedPointer<IDBManager> _manager;
    QSharedPointer<QTimer> _cacheTimer;

    DatabaseContext _databaseContext;
    Logger *_logger = LogFactory::getLogger();

    void clearFileCache();

public:
    EntityManager();

signals:
    void guildInitialized(QSharedPointer<GuildEntity> guildEntity);

public slots:
    void initGuild(QSharedPointer<GuildEntity> payload);
    void initGuildFromPayload(QSharedPointer<GatewayPayload> payload);
    void init();
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions);
    void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions);
    void saveEvent(QSharedPointer<GatewayPayload> payload);
};

#endif // ENTITYMANAGER_H
