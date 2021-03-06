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

        if (_adminRoleIds.contains(id)) {
            return true;
        }
    }

    if (context->getUserId() == BOT_OWNER_ID) {
        return true;
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
        QMap<QString, CommandRestrictions::RestrictionState> mappedStateById = _mappedStateIdsByCommand[command];

        QString userId = context->getUserId().toString();

        if (mappedStateById.contains(userId)) {
            return mappedStateById[userId];
        }

        for (auto jsonRoleId : context->getRoleIds()) {
            QString roleId = jsonRoleId.toString();

            if (mappedStateById.contains(roleId)) {
                return mappedStateById[roleId];
            }
        }

        QString channelId = context->getChannelId().toString();

        if (mappedStateById.contains(channelId)) {
            return mappedStateById[channelId];
        }

        QString guildId = context->getGuildId().toString();

        if (mappedStateById.contains(guildId)) {
            return mappedStateById[guildId];
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
GuildEntity::toggleCommand(const QString &commandName,
                                     const QString &targetId,
                                     CommandRestrictions::RestrictionState state) {

    QMap<QString, CommandRestrictions::RestrictionState> entityUpdateRestrictions;

    if (_commandNamesByScriptName.contains(commandName)) {
        for (auto cmd : _commandNamesByScriptName[commandName]) {
            _mappedStateIdsByCommand[cmd][targetId] = state;

            entityUpdateRestrictions[cmd] = state;
        }
    } else {
        for (auto scriptName : _commandNamesByScriptName.keys()) {
            if (_commandNamesByScriptName[scriptName].contains(commandName)) {
                _mappedStateIdsByCommand[commandName][targetId] = state;

                entityUpdateRestrictions[commandName] = state;
            }
        }
    }

    restrictionsUpdate(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityUpdateRestrictions)));
}

void
GuildEntity::clear(const QString &commandName, const QString &targetId) {
    QMap<QString, CommandRestrictions::RestrictionState> entityUpdateRestrictions;

    if (_commandNamesByScriptName.contains(commandName)) {
        for (auto cmd : _commandNamesByScriptName[commandName]) {
            if (targetId.isEmpty()) {
                _mappedStateIdsByCommand[cmd].clear();
            } else {
                _mappedStateIdsByCommand[cmd].remove(targetId);
            }

            entityUpdateRestrictions[cmd] = CommandRestrictions::REMOVED;
        }
    } else {
        for (auto scriptName : _commandNamesByScriptName.keys()) {
            if (_commandNamesByScriptName[scriptName].contains(commandName)) {
                if (targetId.isEmpty()) {
                    _mappedStateIdsByCommand[commandName].clear();
                } else {
                    _mappedStateIdsByCommand[commandName].remove(targetId);
                }

                entityUpdateRestrictions[commandName] = CommandRestrictions::REMOVED;
            }
        }
    }

    restrictionsRemoval(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityUpdateRestrictions)));
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

    for (auto binding : _gatewayBindings[context->getEventName().toString()]) {
        Job *gatewayEventJob = new Job;

        gatewayEventJob->setContext(*context);

        gatewayEventJob->setFunctionMapping(binding.getFunctionMapping());

        gatewayEventJobs << gatewayEventJob;
    }

    return gatewayEventJobs;
}

QString
GuildEntity::getId() const {
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

void
GuildEntity::setBotOwnerId(const QString &userId) {
    BOT_OWNER_ID = userId;
}

QString
GuildEntity::getBotOwnerId() {
    return BOT_OWNER_ID;
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
    _registeredScripts = registeredScripts;
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
