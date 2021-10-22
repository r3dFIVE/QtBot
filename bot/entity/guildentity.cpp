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

const QString GuildEntity::GUILD_RESTRICTIONS = "GUILD_RESTRICTIONS";
const QString GuildEntity::RESTRICTIONS = "restrictions";
QString GuildEntity::ADMIN_ROLE_NAME = QString();
QString GuildEntity::BOT_OWNER_ID = QString();
CommandRestrictions::RestrictionState GuildEntity::DEFAULT_STATE;

GuildEntity::GuildEntity(const Guild &guild) {
    for (auto jsonRole : guild.getRoles()) {
        Role role(jsonRole.toObject());

        updateRole(role);
    }
}

void
GuildEntity::initRestrictionStates(const QJsonObject &json) {
    QJsonObject restrictions = json[GuildEntity::RESTRICTIONS].toObject();

    QJsonObject::iterator i;
    for (i = restrictions.begin(); i != restrictions.end(); ++i) {
        QMap<QString, CommandRestrictions::RestrictionState> mappings;

        QJsonObject jsonMappings = i->toObject();

        QJsonObject::iterator j;
        for(j = jsonMappings.begin(); j != jsonMappings.end(); ++j) {
            mappings[j.key()] = CommandRestrictions::RestrictionState(j.value().toInt());
        }

        QString unencodedCommand = QString(QByteArray::fromHex(i.key().toUtf8()));

        _mappedStateIdsByCommand[unencodedCommand] = mappings;
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
    default:
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
GuildEntity::updateRestrictionState(const QString &name,
                                     const QString &targetId,
                                     CommandRestrictions::RestrictionState state) {

    QMap<QString, CommandRestrictions::RestrictionState> entityRestrictionsUpdate;

    if (_commandNamesByScriptName.contains(name)) {
        // Script name provided, update all commands
        for (auto cmd : _commandNamesByScriptName[name]) {
            _mappedStateIdsByCommand[cmd][targetId] = state;

            entityRestrictionsUpdate[cmd] = state;
        }
    } else {
        // Check each script's commands.
        QMapIterator<QString, QStringList> it(_commandNamesByScriptName);

        while (it.hasNext()) {

            it.next();

            if (it.value().contains(name)) {
                _mappedStateIdsByCommand[name][targetId] = state;

                entityRestrictionsUpdate[name] = state;
            }
        }
    }

    if (!entityRestrictionsUpdate.isEmpty()) {
        emit restrictionsUpdate(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityRestrictionsUpdate, CommandRestrictions::UPDATE)));
    }
}

void
GuildEntity::updateAllRestrictionStates(const QString &targetId,
                                        CommandRestrictions::RestrictionState state) {

    QMap<QString, CommandRestrictions::RestrictionState> entityRestrictionsUpdate;

    QMapIterator<QString, QStringList> it(_commandNamesByScriptName);

    while(it.hasNext()) {
        it.next();

        for (auto cmd : it.value()) {

            _mappedStateIdsByCommand[cmd][targetId] = state;

            entityRestrictionsUpdate[cmd] = state;
        }
    }

    if (!entityRestrictionsUpdate.isEmpty()) {
        emit restrictionsUpdate(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityRestrictionsUpdate, CommandRestrictions::UPDATE)));
    }
}


void
GuildEntity::removeRestrictionState(const QString &name, const QString &targetId) {
    QMap<QString, CommandRestrictions::RestrictionState> entityRestrictionsUpdate;

     if (name.isEmpty()) {
        removeRestrictionsById(targetId);

        return;
    }

    if (_commandNamesByScriptName.contains(name)) {
        // Script name provided, update all commands
        for (auto cmd : _commandNamesByScriptName[name]) {
            if (targetId.isEmpty()) {
                _mappedStateIdsByCommand[cmd].clear();

                entityRestrictionsUpdate[cmd] = CommandRestrictions::REMOVED;

            } else {
                _mappedStateIdsByCommand[cmd].remove(targetId);

                entityRestrictionsUpdate[cmd] = CommandRestrictions::REMOVED;
            }
        }
    } else {
        QMapIterator<QString, QStringList> it(_commandNamesByScriptName);

        while (it.hasNext()) {

            it.next();

            if (it.value().contains(name)) {
                if (targetId.isEmpty()) {                    
                    _mappedStateIdsByCommand[name].clear();

                    entityRestrictionsUpdate[name] = CommandRestrictions::REMOVED;
                } else if (_mappedStateIdsByCommand[name].contains(targetId)) {
                    _mappedStateIdsByCommand[name].remove(targetId);

                    entityRestrictionsUpdate[name] = CommandRestrictions::REMOVED;
                }
            }
        }
    }

    if (!entityRestrictionsUpdate.isEmpty()) {
        emit restrictionsRemoval(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityRestrictionsUpdate, CommandRestrictions::REMOVE_BY_ID)));
    }
}

void
GuildEntity::removeRestrictionsById(const QString &targetId) {
    QMap<QString, CommandRestrictions::RestrictionState> entityRestrictionsUpdate;

    QMapIterator<QString, QMap<QString, CommandRestrictions::RestrictionState>> r_it(_mappedStateIdsByCommand);

    while (r_it.hasNext()) {
        r_it.next();

        if (r_it.value().contains(targetId)) {
             _mappedStateIdsByCommand[r_it.key()].remove(targetId);

             entityRestrictionsUpdate[r_it.key()] = CommandRestrictions::REMOVED;
        }
    }

    if (!entityRestrictionsUpdate.isEmpty()) {
        emit restrictionsRemoval(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityRestrictionsUpdate, CommandRestrictions::REMOVE_BY_ID)));
    }
}

void GuildEntity::removeAllRestrictionStates()
{
    _mappedStateIdsByCommand.clear();

    emit restrictionsRemoval(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, QString(), QMap<QString, CommandRestrictions::RestrictionState>(), CommandRestrictions::REMOVE_ALL)));
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

    QMapIterator<QString, QString> it(scriptNamesByCommand);

    while (it.hasNext()) {

        it.next();

        _commandNamesByScriptName[it.value()] << it.key();
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
