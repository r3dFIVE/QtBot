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
    static QHash<CoreCommand*, QSharedPointer<CommandBinding>> buildCoreCommandBindings(EventHandler &eventHandler, const QString &guildId) {
        QHash<CoreCommand*, QSharedPointer<CommandBinding>> commands;

        const auto addCommand = [&](const QString& commandName,
                QSharedPointer<IBindingProperties> properties,
                std::function<void(const EventContext &context)> cmd) {
            CoreCommand *coreCommand = new CoreCommand(cmd);

            coreCommand->setGuildId(guildId);

            IBotJob::FunctionMapping functionMapping = qMakePair(commandName, coreCommand);

            QSharedPointer<CommandBinding> binding =
                    QSharedPointer<CommandBinding>(new CommandBinding(commandName, functionMapping, properties));

            commands[coreCommand] = binding;
        };

        QSharedPointer<IBindingProperties> shutdownProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        shutdownProperties->adminOnly = true;

        addCommand(".shutdown", shutdownProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "shutDown",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> reloadProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        reloadProperties->adminOnly = true;

        addCommand(".reload", reloadProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "reloadGuild",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> timedProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        timedProperties->adminOnly = false;

        addCommand(".timed", timedProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "displayTimedJobs",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> timedRemoveProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        timedRemoveProperties->adminOnly = true;

        addCommand(".timedremove", timedRemoveProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "removeTimedJob",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> timedStartProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        timedStartProperties->adminOnly = true;

        addCommand(".timedstart", timedStartProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "startTimedJob",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> timedRestartProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        timedRestartProperties->adminOnly = true;

        addCommand(".timedrestart", timedRestartProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "restartTimedJob",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> timedStopProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        timedStopProperties->adminOnly = true;

        addCommand(".timedstop", timedStopProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "stopTimedJob",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> enableProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        enableProperties->adminOnly = true;

        addCommand(".enable", enableProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "updateRestrictionState",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context),
                                      Q_ARG(CommandRestrictions::RestrictionState, CommandRestrictions::ENABLED));
        });

        QSharedPointer<IBindingProperties> enableAllProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        enableAllProperties->adminOnly = true;

        addCommand(".enableall", enableAllProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "updateAllRestrictionStates",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context),
                                      Q_ARG(CommandRestrictions::RestrictionState, CommandRestrictions::ENABLED));
        });

        QSharedPointer<IBindingProperties> disableProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        disableProperties->adminOnly = true;

        addCommand(".disable", disableProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "updateRestrictionState",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context),
                                      Q_ARG(CommandRestrictions::RestrictionState, CommandRestrictions::DISABLED));
        });

        QSharedPointer<IBindingProperties> disableAllProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        disableAllProperties->adminOnly = true;

        addCommand(".disableall", disableAllProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "updateAllRestrictionStates",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context),
                                      Q_ARG(CommandRestrictions::RestrictionState, CommandRestrictions::DISABLED));
        });

        QSharedPointer<IBindingProperties> clearProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        clearProperties->adminOnly = true;

        addCommand(".clear", clearProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "updateRestrictionState",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context),
                                      Q_ARG(CommandRestrictions::RestrictionState, CommandRestrictions::REMOVED));
        });

        QSharedPointer<IBindingProperties> clearAllProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        clearAllProperties->adminOnly = true;

        addCommand(".clearall", clearAllProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "removeAllRestrictionStates",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        QSharedPointer<IBindingProperties> helpProperties =
                QSharedPointer<IBindingProperties>(new IBindingProperties);

        clearAllProperties->adminOnly = false;

        addCommand(UserHelp::HELP_COMMAND, helpProperties, [&](const EventContext &context) -> void {
            QMetaObject::invokeMethod(&eventHandler,
                                      "getHelp",
                                      Qt::QueuedConnection,
                                      Q_ARG(EventContext, context));
        });

        return commands;
    }
};

#endif // CORECOMMANDS_H
