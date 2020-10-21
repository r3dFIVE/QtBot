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

public:
    GuildEntity() {}
    GuildEntity(const Guild &guild);

    bool hasAdminRole(QSharedPointer<EventContext> context);
    QList<Job *> processEvent(QSharedPointer<EventContext> context);
    QList<TimedBinding> getTimedBindings() const;
    QString id() const;
    void addRole(const Role &role);
    void setCommandBindings(const QList<CommandBinding> &commandBindings);
    void setGatewayBindings(const QList<GatewayBinding> &gatewayBindings);
    void setId(const QString &id);
    void setCommandNamesByScriptName(QMap<QString, QString> &scriptNamesByCommand);
    void setMappedStateIdsByCommand(QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> > mappedStateIdsByCommand);
    void setRegisteredScripts(const QList<QSharedPointer<IBotJob> > registeredScripts);
    void setTimedBindings(const QList<TimedBinding> &timedBindings);
    void updateRole(const Role &role);
    void updateStateIdsByCommand(const EventContext &context, CommandRestrictions::RestrictionState state);
    void removeRole(const QString &roleId);

    void enableCommand(const EventContext &context);
    void disableCommand(const EventContext &context);
    void clearCommandForId(const EventContext &context);
    void clearCommand(const EventContext &context);

    static void setAdminRoleName(const QString &roleName);
    static void setBotOwnerId(const QString &userId);
    static void setDefaultRestrictionState(const QString &state);

private:
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

signals:
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions);
    void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions);
};

#endif // GUILDENTITY_H
