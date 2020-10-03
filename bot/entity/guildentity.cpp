#include "guildentity.h"

#include "payloads/guildroleupdate.h"
#include "payloads/user.h"
#include "botjob/corecommand.h"
#include "botjob/ibotjob.h"
#include "util/enumutils.h"


QString GuildEntity::ADMIN_ROLE_NAME = QString();
QString GuildEntity::BOT_OWNER_ID = QString();
GuildEntity::RestrictionScheme GuildEntity::DEFAULT_SCHEME;


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

    if (_mappedSchemeIdsByCommand.contains(command)) {
        QMap<QString, RestrictionScheme> mappedSchemeById = _mappedSchemeIdsByCommand[command];

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

    return DEFAULT_SCHEME;
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
GuildEntity::setDefaultRestrictionScheme(const QString &scheme) {
    DEFAULT_SCHEME = EnumUtils::keyToValue<GuildEntity::RestrictionScheme>(scheme);
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
