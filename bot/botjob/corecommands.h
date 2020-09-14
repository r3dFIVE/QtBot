#ifndef CORECOMMANDS_H
#define CORECOMMANDS_H

#include "bot.h"
#include "commandbinding.h"
#include "corecommand.h"
#include "logging/logfactory.h"
#include "botjob/ibotjob.h"
#include "eventhandler.h"

class CoreCommands {

public:

    static QList<CommandBinding> buildCoreCommandBindings(EventHandler &eventHandler, const QString &guildId) {
        QList<CommandBinding> commands;

        const auto addCommand = [&](auto commandName, auto cmd) {
            QSharedPointer<CoreCommand> coreCommand = QSharedPointer<CoreCommand>(new CoreCommand(cmd));

            coreCommand->setGuildId(guildId);

            IBotJob::FunctionMapping functionMapping = qMakePair(commandName, coreCommand);

            commands << CommandBinding(commandName, functionMapping);
        };

        addCommand(".reload", [&](const EventContext &context) -> void {
            Q_UNUSED(context);            

            QMetaObject::invokeMethod(&eventHandler, &EventHandler::reloadAllAvailableGuilds, Qt::QueuedConnection);
        });

        addCommand(".timed", [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "displayTimedJobs",
                                     Qt::QueuedConnection,
                                     Q_ARG(EventContext, context));
        });

        addCommand(".timedremove", [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "removeTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".timedresume", [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "resumeTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".timedstart", [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "startTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".timedstop", [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "stopTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        return commands;
    }
};

#endif // CORECOMMANDS_H
