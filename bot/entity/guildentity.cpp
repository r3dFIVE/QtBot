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

void
GuildEntity::invoke(QSharedPointer<EventContext> context) {
    QString command = context->command.toString();

    if (_registry.contains(command)) {
        QStringList ids;

        ids << context->guild_id.toString()
            << context->channel_id.toString()
            << context->author["id"].toString();

        if (canInvoke(command, ids)) {
            ICommand::CommandMapping mapping = _registry[command];

            mapping.second->execute(mapping.first.toUtf8(), context);
        }
    }
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
GuildEntity::setRegistry(const QMap<QString, QPair<QString, QSharedPointer<ICommand> > > &registry) {
    _registry = registry;
}
