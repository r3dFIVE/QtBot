#include "guildentity.h"

#include "payloads/guildroleupdate.h"
#include "payloads/user.h"
#include "botjob/corecommand.h"
#include "botjob/ibotjob.h"
#include "util/enumutils.h"


QString GuildEntity::ADMIN_ROLE_NAME = QString();
QString GuildEntity::BOT_OWNER_ID = QString();
CommandRestrictions::RestrictionState GuildEntity::DEFAULT_STATE;


GuildEntity::GuildEntity(const Guild &guild) {
    for (auto jsonRole : guild.getRoles()) {
        updateRole(Role(jsonRole.toObject()));
    }
}

bool
GuildEntity::hasAdminRole(QSharedPointer<EventContext> context) {
    for (auto roleId : context->getRoleIds()) {
        QString id = roleId.toString();

        if (_adminRoleIds.contains(id) || context->getUserId() == BOT_OWNER_ID) {
            return true;
        }
    }

    return false;
}

bool
GuildEntity::canInvoke(QSharedPointer<EventContext> context, const QString &command) {
    if (hasAdminRole(context)) {
        return true;
    }

    if (_commandBindings[command].isAdminOnly()) {
        return false;
    }

    if (_mappedStateIdsByCommand.contains(command)) {
        QMap<QString, CommandRestrictions::RestrictionState> mappedSchemeById = _mappedStateIdsByCommand[command];

        QString userId = context->getUserId().toString();

        if (mappedSchemeById.contains(userId)) {
            return mappedSchemeById[userId];
        }

        for (auto jsonRoleId : context->getRoleIds()) {
            QString roleId = jsonRoleId.toString();

            if (mappedSchemeById.contains(roleId)) {
                return mappedSchemeById[roleId];
            }
        }

        QString channelId = context->getChannelId().toString();

        if (mappedSchemeById.contains(channelId)) {
            return mappedSchemeById[channelId];
        }

        QString guildId = context->getGuildId().toString();

        if (mappedSchemeById.contains(guildId)) {
            return mappedSchemeById[guildId];
        }
    }

    return DEFAULT_STATE;
}

QString
GuildEntity::parseCommandToken(const QString &message) const {
    int start = -1;
    int i;

    for (i = 0; i < message.size(); i++) {
        if (start < 0 && message[i].isSpace()) {
            continue;
        } else if (start < 0 && !message[i].isSpace()) {
            start = i;
        } else if (start >= 0 && message[i].isSpace()) {
            break;
        }
    }

    if (start >= 0) {
        return message.mid(start, i - start);
    } else {
        return QString();
    }
}

QList<Job *>
GuildEntity::processEvent(QSharedPointer<EventContext> context) {
    GatewayEvent::Event gatewayEvent = EnumUtils::keyToValue<GatewayEvent::Event>(context->getEventName());

    QList<Job *> jobs; //QThreadPool will auto delete jobs on completion.

    Job *commandJob = nullptr;

    switch (gatewayEvent) {
    case GatewayEvent::MESSAGE_CREATE:
    case GatewayEvent::MESSAGE_UPDATE:
        commandJob = getCommandJob(context);
        break;
    case GatewayEvent::GUILD_ROLE_UPDATE:
        updateRole(Role(context->getSourcePayload()[GuildRoleUpdate::ROLE].toObject()));
        break;
    case GatewayEvent::GUILD_ROLE_DELETE:
        removeRole(context->getRoleId().toString());
        break;
    }

    if (commandJob) {
        jobs << commandJob;
    }

    return jobs << getGatewayEventJobs(context);
}

QList<TimedBinding>
GuildEntity::getTimedBindings() const {
    return _timedBindings;
}

void
GuildEntity::setTimedBindings(const QList<TimedBinding> &timedBindings) {
    _timedBindings = timedBindings;
}

void
GuildEntity::updateRole(const Role &role) {
    QString roleId = role.getId().toString();

    _rolesByRoleId[roleId] = role;

    QString roleName = role.getName().toString();

    if (roleName.compare(ADMIN_ROLE_NAME, Qt::CaseInsensitive) != 0) {
        _adminRoleIds.removeAll(roleId);
    } else if (!_adminRoleIds.contains(roleId)) {
        _adminRoleIds << roleId;
    }
}

void
GuildEntity::removeRole(const QString &roleId) {
    _adminRoleIds.removeAll(roleId);

    _rolesByRoleId.remove(roleId);
}

void
GuildEntity::enableCommand(const EventContext &context) {
    updateStateIdsByCommand(context, CommandRestrictions::ENABLED);
}

void
GuildEntity::disableCommand(const EventContext &context) {
    updateStateIdsByCommand(context, CommandRestrictions::DISABLED);
}

void
GuildEntity::updateStateIdsByCommand(const EventContext &context, CommandRestrictions::RestrictionState state) {
    QString commandName = context.getArgs()[1].toString();

    QString targetId = context.getArgs()[2].toString();

    QMap<QString, CommandRestrictions::RestrictionState> entityUpdateRestrictions;

    if (_commandNamesByScriptName.contains(commandName)) {
        for (QJsonValue cmd : _commandNamesByScriptName[commandName]) {
            _mappedStateIdsByCommand[cmd.toString()][targetId] = state;

            entityUpdateRestrictions[cmd.toString()] = state;
        }
    } else {
        for (QString scriptName : _commandNamesByScriptName.keys()) {
            _mappedStateIdsByCommand[commandName][targetId] = state;

            entityUpdateRestrictions[commandName] = state;
        }
    }

    restrictionsUpdate(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityUpdateRestrictions)));
}

void
GuildEntity::clearCommandForId(const EventContext &context) {
    QString commandName = context.getArgs()[1].toString();

    QString targetId = context.getArgs()[2].toString();

    QMap<QString, CommandRestrictions::RestrictionState> entityUpdateRestrictions;

    if (_commandNamesByScriptName.contains(commandName)) {
        for (QJsonValue cmd : _commandNamesByScriptName[commandName]) {
            _mappedStateIdsByCommand[cmd.toString()].remove(targetId);

            entityUpdateRestrictions[cmd.toString()] = CommandRestrictions::DISABLED;
        }
    } else {
        _mappedStateIdsByCommand[commandName].remove(targetId);

        entityUpdateRestrictions[commandName] = CommandRestrictions::DISABLED;
    }

    restrictionsRemoval(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityUpdateRestrictions)));
}

void
GuildEntity::clearCommand(const EventContext &context) {
    QString commandName = context.getArgs()[1].toString();

    QMap<QString, CommandRestrictions::RestrictionState> entityUpdateRestrictions;

    if (_commandNamesByScriptName.contains(commandName)) {
        for (QJsonValue cmd : _commandNamesByScriptName[commandName]) {
            _mappedStateIdsByCommand[cmd.toString()].clear();

            entityUpdateRestrictions[cmd.toString()] = CommandRestrictions::DISABLED;
        }
    } else {
        _mappedStateIdsByCommand[commandName].clear();

        entityUpdateRestrictions[commandName] = CommandRestrictions::DISABLED;
    }

    restrictionsRemoval(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, "", entityUpdateRestrictions)));
}

Job*
GuildEntity::getCommandJob(QSharedPointer<EventContext> context) {
    QString command = parseCommandToken(context->getContent().toString());

    Job *commandJob = nullptr;

    if (_commandBindings.contains(command) && canInvoke(context, command)) {
       commandJob = new Job;

       context->splitArgs();

       commandJob->setContext(*context);

       commandJob->setFunctionMapping(_commandBindings[command].getFunctionMapping());
    }

    return commandJob;
}

QList<Job *>
GuildEntity::getGatewayEventJobs(QSharedPointer<EventContext> context) const {
    QList<Job *> gatewayEventJobs;

    for (GatewayBinding binding : _gatewayBindings[context->getEventName().toString()]) {
        Job *gatewayEventJob = new Job;

        gatewayEventJob->setContext(*context);

        gatewayEventJob->setFunctionMapping(binding.getFunctionMapping());

        gatewayEventJobs << gatewayEventJob;
    }

    return gatewayEventJobs;
}

QString
GuildEntity::id() const {
    return _id;
}

void
GuildEntity::addRole(const Role &role) {
    updateRole(role);
}

void
GuildEntity::setAdminRoleName(const QString &roleName) {
    ADMIN_ROLE_NAME = roleName;
}

void GuildEntity::setBotOwnerId(const QString &userId) {
    BOT_OWNER_ID = userId;
}

void
GuildEntity::setDefaultRestrictionState(const QString &state) {
    DEFAULT_STATE = EnumUtils::keyToValue<CommandRestrictions::RestrictionState>(state);
}

void
GuildEntity::setId(const QString &id) {
    _id = id;
}

void
GuildEntity::setRegisteredScripts(const QList<QSharedPointer<IBotJob> > registeredScripts) {
    _registeredScripts.clear();

    _registeredScripts << registeredScripts;
}

void
GuildEntity::setCommandNamesByScriptName(QMap<QString, QString> &scriptNamesByCommand) {
    _commandNamesByScriptName.clear();

    for (auto commandName : scriptNamesByCommand.keys()) {
        QString scriptName = scriptNamesByCommand[commandName];

        _commandNamesByScriptName[scriptName] << commandName;
    }
}

void
GuildEntity::setMappedStateIdsByCommand(QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> > mappedStateIdsByCommand) {
    _mappedStateIdsByCommand = mappedStateIdsByCommand;
}

void
GuildEntity::setCommandBindings(const QList<CommandBinding> &commandBindings) {
    _commandBindings.clear();

    for (auto binding : commandBindings) {
        _commandBindings[binding.getCommandName()] = binding;
    }
}

void
GuildEntity::setGatewayBindings(const QList<GatewayBinding> &gatewayBindings) {
    _gatewayBindings.clear();

    for (auto binding : gatewayBindings) {
        if (_gatewayBindings.contains(binding.getEventName())) {
            _gatewayBindings[binding.getEventName()] << binding;

        } else {
            _gatewayBindings[binding.getEventName()] = QList<GatewayBinding>() << binding;
        }
    }
}
