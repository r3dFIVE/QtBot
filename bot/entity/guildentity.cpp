#include "guildentity.h"

#include "payloads/user.h"
#include "botjob/corecommand.h"
#include "botjob/ibotjob.h"
#include "util/enumutils.h"


bool
GuildEntity::canInvoke(QString command, QStringList ids) {
    bool isInvokable = _scheme;

    for (QString id : ids) {
        if (_scheme == DISABLED) {
            if (_mappedSchemeIdsByCommand.contains(command)) {
                isInvokable = _mappedSchemeIdsByCommand[command].contains(id);

                break;
            }
        } else {
            if (_mappedSchemeIdsByCommand.contains(command)) {
                isInvokable = !_mappedSchemeIdsByCommand[command].contains(id);

                break;
            }
        }
    }

    return isInvokable;
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
GuildEntity::getBotJobs(QSharedPointer<EventContext> context) {
    GatewayEvent::Event gatewayEvent = EnumUtils::keyToValue<GatewayEvent::Event>(context->getEventName());

    QList<Job *> jobs; //QThreadPool will auto delete jobs on completion.

    Job *commandJob = nullptr;

    switch (gatewayEvent) {
    case GatewayEvent::MESSAGE_CREATE:
    case GatewayEvent::MESSAGE_UPDATE:
        commandJob = getCommandJob(context);
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

Job*
GuildEntity::getCommandJob(QSharedPointer<EventContext> context) {
    QString command = parseCommandToken(context->getContent().toString());

    Job *commandJob = nullptr;

    if (_commandBindings.contains(command)) {
       QStringList ids;

       ids << context->getGuildId().toString()
           << context->getChannelId().toString()
           << context->getAuthor()[User::ID].toString();

       if (canInvoke(command, ids)) {
           commandJob = new Job;

           commandJob->setContext(*context);

           commandJob->setFunctionMapping(_commandBindings[command].getFunctionMapping());
       }
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
