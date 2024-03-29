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
#include "botjob/userhelp.h"

const QString GuildEntity::DEFAULT_GUILD_ID = "0";
const QString GuildEntity::GUILD_RESTRICTIONS = "GUILD_RESTRICTIONS";
const QString GuildEntity::RESTRICTIONS = "restrictions";
//first channel_id == guild_id for guild, use -1 for guild-level alias
const QString GuildEntity::GUILD_ID_ALIAS = "-1";
QString GuildEntity::ADMIN_ROLE_NAME = QString();
QString GuildEntity::BOT_OWNER_ID = QString();
CommandRestrictions::RestrictionState GuildEntity::DEFAULT_STATE;

GuildEntity::GuildEntity(const Guild &guild, QObject *parent) : QObject{parent}  {
    for (auto jsonRole : guild.getRoles()) {
        Role role(jsonRole.toObject());

        checkForAdminRole(role);
    }

    _adminIds << BOT_OWNER_ID;

    setGuildOwnerId(guild.getOwnerId().toString());
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
GuildEntity::isAdmin(const EventContext& context) {
    if (_adminIds.contains(context.getUserId().toString())) {
        return true;
    }

    for (auto roleId : context.getRoleIds()) {
        if (_adminIds.contains(roleId.toString())) {
            return true;
        }
    }

    return false;
}

bool
GuildEntity::canInvoke(const EventContext &context, const QString &command) {

    if (_commandBindings.contains(command)) {
        if (!_commandBindings[command]->ignoreAdmin()) {
            if (isAdmin(context)) {
                return true;
            }

            if (_commandBindings[command]->isAdminOnly()) {
                return false;
            }
        }
    } else if (_gatewayBindings.contains(command)) {
        if (!_gatewayBindings[command]->ignoreAdmin()) {
            if (isAdmin(context)) {
                return true;
            }

            if (_gatewayBindings[command]->isAdminOnly()) {
                return false;
            }
        }
    } else {
        return false;
    }

    if (_mappedStateIdsByCommand.contains(command)) {
        QMap<QString, CommandRestrictions::RestrictionState> mappedStateById = _mappedStateIdsByCommand[command];

        QString userId = context.getUserId().toString();

        if (mappedStateById.contains(userId)) {
            return mappedStateById[userId];
        }

        for (auto jsonRoleId : context.getRoleIds()) {
            QString roleId = jsonRoleId.toString();

            if (mappedStateById.contains(roleId)) {
                return mappedStateById[roleId];
            }
        }

        QString channelId = context.getChannelId().toString();

        if (mappedStateById.contains(channelId)) {
            return mappedStateById[channelId];
        }

        QString guildId = context.getGuildId().toString();

        if (mappedStateById.contains(GUILD_ID_ALIAS)) {
            return mappedStateById[GUILD_ID_ALIAS];
        }
    }

    if (command == UserHelp::HELP_COMMAND) {
        return true;
    }

    return DEFAULT_STATE;
}

QList<Job *>
GuildEntity::processEvent(QSharedPointer<EventContext> context) {
    GatewayEvent::Event gatewayEvent = EnumUtils::keyToValue<GatewayEvent::Event>(context->getEventName());

    Job *commandJob = nullptr;

    switch (gatewayEvent) {
        case GatewayEvent::MESSAGE_CREATE:
        case GatewayEvent::MESSAGE_UPDATE:
            commandJob = getCommandJob(context);
            break;
        case GatewayEvent::GUILD_ROLE_UPDATE:
            checkForAdminRole(Role(context->getSourcePayload()[GuildRoleUpdate::ROLE].toObject()));
            break;
        case GatewayEvent::GUILD_ROLE_DELETE:
            removeRole(context->getRoleId().toString());
            break;
        default:
            break;
    }

    QList<Job *> jobs; //QThreadPool will auto delete jobs on completion.

    if (commandJob) {
        jobs << commandJob;
    }

    return jobs << getGatewayEventJobs(context);
}


void
GuildEntity::checkForAdminRole(const Role &role) {
    QString roleId = role.getId().toString();

    QString roleName = role.getName().toString();

    if (roleName.compare(ADMIN_ROLE_NAME, Qt::CaseInsensitive) == 0) {
        _adminIds << roleId;


    } else {
        _adminIds.remove(roleId);

    }
}

void
GuildEntity::removeRole(const QString &roleId) {
    _adminIds.remove(roleId);
}

void
GuildEntity::updateRestrictionStates(const QString &name,
                                     const QString &targetId,
                                     CommandRestrictions::RestrictionState state) {

    if (name.isEmpty()) {
        updateAllRestrictionStates(targetId, state);

        return;
    }

    QMap<QString, CommandRestrictions::RestrictionState> entityRestrictionsUpdate;

    if (_gatewayBindings.contains(name)) {

        updateState(entityRestrictionsUpdate, name, targetId, state);

    } else if (_commandNamesByScriptName.contains(name)) {
        // Script name provided, update all commands
        for (auto &commandName : _commandNamesByScriptName[name]) {
            updateState(entityRestrictionsUpdate, commandName, targetId, state);
        }
    } else {
        // Check each script's commands.
        QMapIterator<QString, QStringList> it(_commandNamesByScriptName);

        while (it.hasNext()) {

            it.next();

            if (it.value().contains(name)) {
                updateState(entityRestrictionsUpdate, name, targetId, state);
            }
        }
    }

    updateTimedBindingState(entityRestrictionsUpdate, name, state);

    if (!entityRestrictionsUpdate.isEmpty()) {
        emit restrictionsUpdate(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityRestrictionsUpdate)));
    }
}

void
GuildEntity::updateState(QMap<QString, CommandRestrictions::RestrictionState> &restrictionUpdates,
                         const QString &name,
                         const QString &targetId,
                         CommandRestrictions::RestrictionState state) {

    if (state == CommandRestrictions::REMOVED) {
        if (targetId.isEmpty()) {
            _mappedStateIdsByCommand[name].clear();
        } else {
            _mappedStateIdsByCommand[name].remove(targetId);
        }

    } else {
        _mappedStateIdsByCommand[name][targetId] = state;
    }

    restrictionUpdates[name] = state;
}

void
GuildEntity::updateAllRestrictionStates(const QString &targetId,
                                        CommandRestrictions::RestrictionState state) {

    QMap<QString, CommandRestrictions::RestrictionState> entityRestrictionsUpdate;

    QMapIterator<QString, QStringList> c_it(_commandNamesByScriptName);

    while(c_it.hasNext()) {
        c_it.next();

        for (auto cmd : c_it.value()) {
            updateState(entityRestrictionsUpdate, cmd, targetId, state);
        }
    }

    QMapIterator<QString, QSharedPointer<GatewayBinding>> g_it(_gatewayBindings);

    while(g_it.hasNext()) {
        g_it.next();

        updateState(entityRestrictionsUpdate, g_it.key(), targetId, state);
    }

    updateAllTimedBindings(entityRestrictionsUpdate, state);

    if (!entityRestrictionsUpdate.isEmpty()) {
        emit restrictionsUpdate(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, targetId, entityRestrictionsUpdate)));
    }
}

void
GuildEntity::updateAllTimedBindings(QMap<QString, CommandRestrictions::RestrictionState> &restrictionUpdates,
                                 CommandRestrictions::RestrictionState state) {
    for (QSharedPointer<TimedBinding> binding : _timedBindings) {
        updateTimedBindingState(restrictionUpdates, binding->getName(), state);
    }

    for (QSharedPointer<TimedBinding> binding : _disabledTimedBindings) {
        updateTimedBindingState(restrictionUpdates, binding->getName(), state);
    }
}

void
GuildEntity::updateTimedBindingState(QMap<QString, CommandRestrictions::RestrictionState> &restrictionUpdates,
                                     const QString &bindingName,
                                     const CommandRestrictions::RestrictionState state) {


    if (_disabledTimedBindings.contains(bindingName)) {
        if (state == CommandRestrictions::ENABLED) {
            _timedBindings[bindingName] = _disabledTimedBindings[bindingName];

            _disabledTimedBindings.remove(bindingName);

            _timedBindings[bindingName]->start();
        }

        updateState(restrictionUpdates, bindingName, _id, state);
    } else if (_timedBindings.contains(bindingName)) {
        if (state == CommandRestrictions::DISABLED)  {
            _disabledTimedBindings[bindingName] = _timedBindings[bindingName];

            _disabledTimedBindings[bindingName]->stop();

            _timedBindings.remove(bindingName);
        }

        updateState(restrictionUpdates, bindingName, _id, state);
    }
}

void
GuildEntity::removeAllRestrictionStates() {
    _mappedStateIdsByCommand.clear();

    emit restrictionsUpdate(QSharedPointer<CommandRestrictions>(new CommandRestrictions(_id, QString(), QMap<QString, CommandRestrictions::RestrictionState>())));
}

Job*
GuildEntity::getCommandJob(QSharedPointer<EventContext> context) {
    Job *commandJob = nullptr;

    if (context->getArgs().isEmpty()) {
        return commandJob;
    }

    QString command = context->getArgs()[0].toString();

    if (canInvoke(*context, command)) {
       commandJob = new Job(*context, _commandBindings[command]->getFunctionMapping());
    }

    return commandJob;
}

QList<Job *>
GuildEntity::getGatewayEventJobs(QSharedPointer<EventContext> context) {
    QList<Job *> gatewayEventJobs;

    for (auto binding : _gatewayBindingsByEventName[context->getEventName().toString()]) {
        if (!canInvoke(*context, binding->getName())) {
            continue;
        }

        gatewayEventJobs << new Job(*context, binding->getFunctionMapping());
    }

    return gatewayEventJobs;
}

QString
GuildEntity::getId() const {
    return _id;
}

QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> >
GuildEntity::getMappedStateIdsByCommand() {
    return _mappedStateIdsByCommand;
}

void
GuildEntity::addRole(const Role &role) {
    checkForAdminRole(role);
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
GuildEntity::addCommandBinding(BotScript *botScript, QSharedPointer<CommandBinding> binding) {
    _bindingsByScript[botScript] << binding;

    _commandBindings[binding->getName()] = binding;
}

void
GuildEntity::addGatewayBinding(BotScript *botScript, QSharedPointer<GatewayBinding> binding) {
    _bindingsByScript[botScript] << binding;

    _gatewayBindings[binding->getName()] = binding;

    if (_gatewayBindingsByEventName.contains(binding->getEventName())) {
        _gatewayBindingsByEventName[binding->getEventName()] << binding;

    } else {
        _gatewayBindingsByEventName[binding->getEventName()] = QList<QSharedPointer<GatewayBinding>>() << binding;
    }
}

void
GuildEntity::addTimedBinding(BotScript *botScript, QSharedPointer<TimedBinding> binding, const bool checkState) {
    _bindingsByScript[botScript] << binding;

    if (checkState) {
        if (isTimedJobEnabled(*binding)) {
            _timedBindings[binding->getName()] = binding;
        } else {
            _disabledTimedBindings[binding->getName()] = binding;
        }
    } else {
        _timedBindings[binding->getName()] = binding;
    }
}

QList<QSharedPointer<TimedBinding>>
GuildEntity::getTimedBindings() const {
    return _timedBindings.values();
}

bool
GuildEntity::hasTimedJobs() const {
    return !_timedBindings.isEmpty();
}

QList<Job *>
GuildEntity::getReadyTimedJobs() {
    QList<Job *> readyJobs;

    QMapIterator<QString, QSharedPointer<TimedBinding>> it(_timedBindings);

    while (it.hasNext()) {
        it.next();

        QSharedPointer<TimedBinding> timedBinding = it.value();

        if (QDateTime::currentSecsSinceEpoch() == timedBinding->getStartedAt()) {
            continue;

        } else if (timedBinding->isRunning() && timedBinding->getRemaining() <= 0) {
            EventContext context = timedBinding->getEventContext();

            context.setGuildId(_id);

            Job *timedJob = new Job;

            timedJob->setContext(context);

            timedJob->setFunctionMapping(timedBinding->getFunctionMapping());

            readyJobs << timedJob;

            if (timedBinding->isSingleShot()) {
                _disabledTimedBindings[it.key()] = _timedBindings[it.key()];

                _timedBindings.remove(it.key());

            } else {
                _timedBindings[it.key()]->start();
            }
        }
    }

    return readyJobs;
}


void
GuildEntity::clearTimedJobs() {
    _timedBindings.clear();
}

bool
GuildEntity::validateTimedJobIndex(const int index) {
    if (_timedBindings.isEmpty()) {
        return false;
    }

    if (index >= 0 && index <= _timedBindings.size()) {
        return true;
    }

    _logger->debug(QString("Index (%1) is out of bounds for timed bindings for GuildId: %2")
                   .arg(index)
                   .arg(_id));

    return false;
}

void
GuildEntity::removeTimedJobById(const QString &jobId) {
    QMapIterator<QString, QSharedPointer<TimedBinding>> it(_timedBindings);

    while (it.hasNext()) {
        it.next();

        if (_timedBindings[it.key()]->id() == jobId) {
            _timedBindings.remove(it.key());
        }
    }
}

void
GuildEntity::removeTimedJob(const int index) {
    if (!validateTimedJobIndex(index)) {
        return;
    }

    QString bindingName = _timedBindings.keys()[index];

    _timedBindings.remove(bindingName);
}

void
GuildEntity::startTimedJob(const int index) {
    if (!validateTimedJobIndex(index)) {
        return;
    }

    QString bindingName = _timedBindings.keys()[index];

    _timedBindings[bindingName]->start();
}

void
GuildEntity::restartTimedJob(const int index) {
    if (!validateTimedJobIndex(index)) {
        return;
    }

    QString bindingName = _timedBindings.keys()[index];

    _timedBindings[bindingName]->restart();
}

void
GuildEntity::stopTimedJob(const int index) {
    if (!validateTimedJobIndex(index)) {
        return;
    }

    QString bindingName = _timedBindings.keys()[index];

    _timedBindings[bindingName]->stop();
}

void
GuildEntity::initTimedJobs() {    
    QMapIterator<QString, QSharedPointer<TimedBinding>> it(_timedBindings);

    while (it.hasNext()) {
        it.next();

        _timedBindings[it.key()]->start();
    }
}

void
GuildEntity::clearBindings() {
    _bindingsByScript.clear();

    _timedBindings.clear();

    _disabledTimedBindings.clear();

    _gatewayBindingsByEventName.clear();

    _commandBindings.clear();

    _commandNamesByScriptName.clear();

    _gatewayBindings.clear();
}

bool
GuildEntity::isTimedJobEnabled(const TimedBinding &binding) {
    if (binding.forceEnable()) {
        return true;
    }

    QString bindingName = binding.getName();

    if (_mappedStateIdsByCommand.contains(bindingName)) {
        if (_mappedStateIdsByCommand[bindingName].contains(GUILD_ID_ALIAS)) {
            return _mappedStateIdsByCommand[bindingName][GUILD_ID_ALIAS];
        }
    }

    return DEFAULT_STATE;
}

void
GuildEntity::setGuildOwnerId(const QString &guildOwnerId) {
    _guildOwnerId = guildOwnerId;

    _adminIds << guildOwnerId;
}

QString
GuildEntity::getGuildOwnerId() const {
    return _guildOwnerId;
}

UserHelp*
GuildEntity::getUserHelp(const EventContext &context) {
    QString userId = context.getUserId().toString();

    QString channelId = context.getChannelId().toString();

    if (isAdmin(context)) {
        return new UserHelp(_bindingsByScript, userId, channelId, _id, true);
    }

    QMapIterator<QString, QSharedPointer<CommandBinding>> it(_commandBindings);

    QMap<BotScript*, QList<QSharedPointer<IBinding>>> enabledBindings;

    while (it.hasNext()) {
        it.next();

        if (canInvoke(context, it.key())) {
            BotScript *botScript = qobject_cast<BotScript*>(it.value()->getFunctionMapping().second);

            enabledBindings[botScript] << it.value();
        }

    }

    enabledBindings.remove(nullptr);

    return new UserHelp(enabledBindings, userId, channelId, _id, false);
}
