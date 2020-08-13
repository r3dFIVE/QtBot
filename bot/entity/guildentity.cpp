#include "guildentity.h"

#include "botjob/ibotjob.h"
#include "payloads/user.h"
#include "botjob/corecommand.h"



bool
GuildEntity::canInvoke(QString command, QStringList ids) {
    bool isInvokable = _scheme;

    for (QString id : ids) {
        if (_scheme == DISABLED) {
            if (_mappedIdsByCommand.contains(command)) {
                isInvokable = _mappedIdsByCommand[command].contains(id);

                break;
            }
        } else {
            if (_mappedIdsByCommand.contains(command)) {
                isInvokable = !_mappedIdsByCommand[command].contains(id);

                break;
            }
        }
    }

    return isInvokable;
}

Job*
GuildEntity::getBotJob(QSharedPointer<EventContext> context) {
    QString command = context->getCommand().toString();

    Job *job = nullptr; //QThreadPool will auto delete on completion.

    if (_commandBindings.contains(command)) {
        QStringList ids;

        ids << context->getGuildId().toString()
            << context->getChannelId().toString()
            << context->getAuthor()[User::ID].toString();

        if (canInvoke(command, ids)) {
            job = new Job;

            job->setContext(*context);

            job->setFunctionMapping(_commandBindings[command].getFunctionMapping());
        }
    }

    return job;
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
GuildEntity::setCommandBindings(const QList<CommandBinding> &commandBindings) {
    for (auto binding : commandBindings) {
        _commandBindings[binding.getCommandName()] = binding;
    }
}
