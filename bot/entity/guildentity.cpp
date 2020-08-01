#include "guildentity.h"

#include "util/corecommand.h"

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

BotJob*
GuildEntity::getBotJob(QSharedPointer<EventContext> context) {
    QString command = context->command.toString();

    BotJob *botJob = nullptr; //QThreadPool will auto delete on completion.

    if (_registry.contains(command)) {
        QStringList ids;

        ids << context->guild_id.toString()
            << context->channel_id.toString()
            << context->author["id"].toString();        

        if (canInvoke(command, ids)) {
            botJob = new BotJob;
            botJob->setContext(*context);
            botJob->setCommandMapping(_registry[command]);
        }
    }

    return botJob;
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
GuildEntity::setRegistry(const QMap<QString, QPair<QString, QSharedPointer<IBotJob> > > &registry) {
    _registry = registry;
}
