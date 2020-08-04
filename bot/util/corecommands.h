#ifndef CORECOMMANDS_H
#define CORECOMMANDS_H

#include "bot.h"
#include "corecommand.h"
#include "serializationutils.h"
#include "logging/logfactory.h"


class CoreCommands {
    typedef std::function<void(const Message &message)> Command;

public:

    static QMap<QString, IBotJob::CommandMapping > buildCommands(Bot &bot, const QString &guildId) {
        QMap<QString, QPair<QString, QSharedPointer<IBotJob> > > commands;

        const auto addCommand = [&](auto name, auto cmd) {
            QSharedPointer<CoreCommand> command = QSharedPointer<CoreCommand>(new CoreCommand(cmd));

            command->setGuildId(guildId);

            commands[name] = qMakePair(name, command);
        };

        addCommand(".reload", [&](const EventContext &context) -> void {
            Q_UNUSED(context);

            QMetaObject::invokeMethod(&bot, &Bot::reloadAllCommands, Qt::QueuedConnection);
        });

        return commands;
    }
};

#endif // CORECOMMANDS_H
