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

#include "botjob/userhelp.h"
#include "botjob/botscript.h"
#include "commandrestrictions.h"
#include "botjob/commandbinding.h"
#include "botjob/gatewaybinding.h"
#include "botjob/timedbinding.h"
#include "botjob/job.h"
#include "payloads/eventcontext.h"
#include "payloads/guild.h"
#include "payloads/role.h"

class ScriptManager;

class GuildEntity : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);

    static CommandRestrictions::RestrictionState DEFAULT_STATE;
    static QString ADMIN_ROLE_NAME;
    static QString BOT_OWNER_ID;

    QMap<BotScript*, QList<QSharedPointer<IBinding>>> _bindingsByScript;
    QMap<QString, QSharedPointer<TimedBinding>> _timedBindings;
    QMap<QString, QSharedPointer<TimedBinding>> _disabledTimedBindings;    
    QMap<QString, QList<QSharedPointer<GatewayBinding>>> _gatewayBindingsByEventName;
    QMap<QString, QSharedPointer<CommandBinding>> _commandBindings;    
    QMap<QString, QStringList> _commandNamesByScriptName;
    QMap<QString, QSharedPointer<GatewayBinding>> _gatewayBindings;


    QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> > _mappedStateIdsByCommand;

    QString _id = DEFAULT_GUILD_ID;
    QString _guildOwnerId;
    QSet<QString> _adminIds;

    Job* getCommandJob(QSharedPointer<EventContext> context);
    QList<Job*> getGatewayEventJobs(QSharedPointer<EventContext> context);
    void clearCommand(const QString &commandName, const QString &targetId);
    void updateState(QMap<QString, CommandRestrictions::RestrictionState> &restrictionUpdates,
                     const QString &name,
                     const QString &targetId,
                     CommandRestrictions::RestrictionState state);
    bool isTimedJobEnabled(const TimedBinding &binding);
    void setGuildOwnerId(const QString &guildOwnerId);


public:
    GuildEntity(QObject *parent = nullptr) : QObject{parent} {}
    GuildEntity(const Guild &guild, QObject *parent = nullptr);

    void updateTimedBindingState(QMap<QString, CommandRestrictions::RestrictionState> &restrictionUpdates,
                                 const QString &bindingName,
                                 const CommandRestrictions::RestrictionState state);
    void updateTimedBinding(QMap<QString, CommandRestrictions::RestrictionState> &restrictionUpdates,
                             const QString &bindingName,
                             CommandRestrictions::RestrictionState state);
    void updateAllTimedBindings(QMap<QString, CommandRestrictions::RestrictionState> &restrictionUpdates,
                             CommandRestrictions::RestrictionState state);

    static const QString DEFAULT_GUILD_ID;
    static const QString GUILD_RESTRICTIONS;
    static const QString RESTRICTIONS;
    static const QString GUILD_ID_ALIAS;

    void initRestrictionStates(const QJsonObject &json);
    bool isAdmin(const EventContext& context);
    bool canInvoke(const EventContext& context, const QString &command);
    QList<Job *> processEvent(QSharedPointer<EventContext> context);
    QList<QSharedPointer<TimedBinding>> getTimedBindings() const;
    QString getId() const;
    QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> > getMappedStateIdsByCommand();
    void addRole(const Role &role);
    void addCommandBinding(BotScript *botScript, QSharedPointer<CommandBinding> binding);
    void addGatewayBinding(BotScript *botScript, QSharedPointer<GatewayBinding> binding);
    void addTimedBinding(BotScript *botScript, QSharedPointer<TimedBinding> binding, const bool checkState = false);
    void addRegisteredScript(QSharedPointer<IBotJob> script);
    void setId(const QString &id);
    void setCommandNamesByScriptName(QMap<QString, QString> &scriptNamesByCommand);
    void setMappedStateIdsByCommand(QMap<QString, QMap<QString,
                                    CommandRestrictions::RestrictionState> > mappedStateIdsByCommand);
    void checkForAdminRole(const Role &role);
    void removeRole(const QString &roleId);
    void removeAllRestrictionStates();
    void updateAllRestrictionStates(const QString &targetId,
                                            CommandRestrictions::RestrictionState state);
    void updateRestrictionStates(const QString &commandName,
                       const QString &targetId,
                       CommandRestrictions::RestrictionState state);

    static void setAdminRoleName(const QString &roleName);
    static void setBotOwnerId(const QString &userId);
    static void setDefaultRestrictionState(const QString &state);
    static QString getBotOwnerId();   

    bool hasTimedJobs() const;
    QList<Job *> getReadyTimedJobs();
    void clearTimedJobs();
    bool validateTimedJobIndex(const int index);
    void removeTimedJobById(const QString &jobId);
    void removeTimedJob(const int index);
    void startTimedJob(const int index);
    void restartTimedJob(const int index);
    void stopTimedJob(const int index);
    void initTimedJobs();
    void clearBindings();

    UserHelp *getUserHelp(const EventContext &context);
    QString getGuildOwnerId() const;

signals:
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions);
};

#endif // GUILDENTITY_H
