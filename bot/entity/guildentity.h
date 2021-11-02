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

#ifndef GUILDENTITY_H
#define GUILDENTITY_H

#include <QObject>
#include <QMap>
#include <QQmlEngine>

#include "commandrestrictions.h"
#include "botjob/commandbinding.h"
#include "botjob/gatewaybinding.h"
#include "botjob/timedbinding.h"
#include "botjob/job.h"
#include "payloads/eventcontext.h"
#include "payloads/guild.h"
#include "payloads/role.h"


class GuildEntity : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    static CommandRestrictions::RestrictionState DEFAULT_STATE;
    static QString ADMIN_ROLE_NAME;
    static QString BOT_OWNER_ID;

    QList<QSharedPointer<IBotJob> > _registeredScripts;
    QList<TimedBinding> _timedBindings;
    QMap<QString, Role> _rolesByRoleId;
    QMap<QString, QList<GatewayBinding> > _gatewayBindings;
    QMap<QString, CommandBinding> _commandBindings;
    QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> > _mappedStateIdsByCommand;
    QMap<QString, QStringList> _commandNamesByScriptName;
    QString _id = DEFAULT_GUILD_ID;
    QStringList _adminRoleIds;

    bool canInvoke(QSharedPointer<EventContext> context, const QString &command);
    Job* getCommandJob(QSharedPointer<EventContext> context);
    QList<Job*> getGatewayEventJobs(QSharedPointer<EventContext> context) const;
    QString parseCommandToken(const QString &content) const;
    void clearCommand(const QString &commandName, const QString &targetId);

public:
    GuildEntity() {}
    GuildEntity(const Guild &guild);

    static const QString DEFAULT_GUILD_ID;
    static const QString GUILD_RESTRICTIONS;
    static const QString RESTRICTIONS;

    void initRestrictionStates(const QJsonObject &json);
    bool hasAdminRole(QSharedPointer<EventContext> context);
    QList<Job *> processEvent(QSharedPointer<EventContext> context);
    QList<TimedBinding> getTimedBindings() const;
    QString getId() const;
    void addRole(const Role &role);
    void setCommandBindings(const QList<CommandBinding> &commandBindings);
    void setGatewayBindings(const QList<GatewayBinding> &gatewayBindings);
    void setId(const QString &id);
    void setCommandNamesByScriptName(QMap<QString, QString> &scriptNamesByCommand);
    void setMappedStateIdsByCommand(QMap<QString, QMap<QString,
                                    CommandRestrictions::RestrictionState> > mappedStateIdsByCommand);
    void setRegisteredScripts(const QList<QSharedPointer<IBotJob> > registeredScripts);
    void setTimedBindings(const QList<TimedBinding> &timedBindings);
    void updateRole(const Role &role);
    void removeRole(const QString &roleId);
    void removeRestrictionState(const QString &commandName, const QString &targetId);
    void removeRestrictionStatesForCommand(const QString &commandName);
    void removeRestrictionsById(const QString &targetId);
    void removeAllRestrictionStates();
    void updateRestrictionState(const QString &commandName,
                       const QString &targetId,
                       CommandRestrictions::RestrictionState state);
    void updateAllRestrictionStates(const QString &targetId,
                                    CommandRestrictions::RestrictionState state);

    static void setAdminRoleName(const QString &roleName);
    static void setBotOwnerId(const QString &userId);
    static void setDefaultRestrictionState(const QString &state);
    static QString getBotOwnerId();   

signals:
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions);
    void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions);
};

#endif // GUILDENTITY_H
