#ifndef CORECOMMANDS_H
#define CORECOMMANDS_H

#include "corecommand.h"

#include "bot.h"

#include <logging/logfactory.h>


class CoreCommands {
    typedef std::function<void(const Message &message)> Command;

public:

    static QMap<QString, ICommand::CommandMapping > buildCommands(Bot &bot) {
        QMap<QString, QPair<QString, QSharedPointer<ICommand> > > commands;

        const auto addCommand = [&](auto name, auto cmd) {
            QSharedPointer<CoreCommand> command = QSharedPointer<CoreCommand>(new CoreCommand(cmd));
            commands[name] = qMakePair(name, command);
        };

        addCommand(".reload", [&](const Message &message) -> void {
            Q_UNUSED(message);

            bot.loadRegistrar();
        });

        return commands;
    }
};

#endif // CORECOMMANDS_H
