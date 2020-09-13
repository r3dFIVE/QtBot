#ifndef CORECOMMANDS_H
#define CORECOMMANDS_H

#include "bot.h"
#include "commandbinding.h"
#include "corecommand.h"
#include "logging/logfactory.h"
#include "botjob/ibotjob.h"

class CoreCommands {

public:

    static QList<CommandBinding> buildCoreCommandBindings(Bot &bot, const QString &guildId) {
        QList<CommandBinding> commands;

        const auto addCommand = [&](auto commandName, auto cmd) {
            QSharedPointer<CoreCommand> coreCommand = QSharedPointer<CoreCommand>(new CoreCommand(cmd));

            coreCommand->setGuildId(guildId);

            IBotJob::FunctionMapping functionMapping = qMakePair(commandName, coreCommand);

            commands << CommandBinding(commandName, functionMapping);
        };

        addCommand(".reload", [&](const EventContext &context) -> void {
            Q_UNUSED(context);            

            QMetaObject::invokeMethod(&bot, &Bot::reloadAllCommands, Qt::QueuedConnection);
        });

        addCommand(".timed", [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&bot,
                                     "displayTimedJobs",
                                     Qt::QueuedConnection,
                                     Q_ARG(EventContext, context));
        });

        return commands;
    }
};

#endif // CORECOMMANDS_H
