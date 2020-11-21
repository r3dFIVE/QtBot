/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CORECOMMANDS_H
#define CORECOMMANDS_H

#include "bot.h"
#include "commandbinding.h"
#include "corecommand.h"
#include "eventhandler.h"
#include "logging/logfactory.h"
#include "botjob/ibotjob.h"
#include "qml/sqldatabase.h"


class CoreCommands {

public:

    static QMap<QSharedPointer<CoreCommand>, CommandBinding> buildCoreCommandBindings(EventHandler &eventHandler, const QString &guildId) {
        QMap<QSharedPointer<CoreCommand>, CommandBinding> commands;

        const auto addCommand = [&](const QString& commandName, bool adminOnly, std::function<void(const EventContext &context)> cmd) {
            QSharedPointer<CoreCommand> coreCommand = QSharedPointer<CoreCommand>(new CoreCommand(cmd));

            coreCommand->setGuildId(guildId);

            IBotJob::FunctionMapping functionMapping = qMakePair(commandName, coreCommand.data());

            CommandBinding binding(commandName, functionMapping);

            binding.setAdminOnly(adminOnly);

            commands[coreCommand] = binding;
        };

        addCommand(".reload", true, [&](const EventContext &context) -> void {
            Q_UNUSED(context);            

            SqlDatabase::clearQueries();

            QMetaObject::invokeMethod(&eventHandler, &EventHandler::reloadAllAvailableGuilds, Qt::QueuedConnection);
        });

        addCommand(".timed", false, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "displayTimedJobs",
                                     Qt::QueuedConnection,
                                     Q_ARG(EventContext, context));
        });

        addCommand(".timedremove", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "removeTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".timedresume", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "resumeTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".timedstart", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "startTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".timedstop", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "stopTimedJob",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".enable", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "enableCommand",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".disable", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "disableCommand",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".clear", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "clearCommandForId",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        addCommand(".clearall", true, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                     "clearCommand",
                                     Qt::QueuedConnection,
                                     Q_ARG(const EventContext&, context));
        });

        return commands;
    }
};

#endif // CORECOMMANDS_H
