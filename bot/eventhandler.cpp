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

#include "eventhandler.h"

#include <QDebug>
#include <QThreadPool>

#include "util/globals.h"
#include "util/enumutils.h"
#include "botjob/botscript.h"
#include "botjob/job.h"


const int EventHandler::JOB_POLL_MS = 500;

EventHandler::EventHandler(QSharedPointer<Settings> settings) {
    GuildEntity::setBotOwnerId(settings->value(SettingsParam::Bot::OWNER_ID).toString());

    GuildEntity::setAdminRoleName(settings->value(SettingsParam::Bot::ADMIN_ROLE_NAME).toString());

    QString defaultScheme = settings->value(SettingsParam::Bot::RESTRICTION_STATE).toString();

    GuildEntity::setDefaultRestrictionState(defaultScheme);

    _discordAPI = QSharedPointer<DiscordAPI>(new DiscordAPI);
}

void
EventHandler::init() {
    _logger = LogFactory::getLogger();

    _jobQueueTimer = QSharedPointer<QTimer>(new QTimer);

    connect(_jobQueueTimer.data(), &QTimer::timeout, this, &EventHandler::processJobQueue);

    _timedJobTimer = QSharedPointer<QTimer>(new QTimer);

    connect(_timedJobTimer.data(), &QTimer::timeout, this, &EventHandler::processTimedJobs);
}

void
EventHandler::processJobQueue() {
    Job *readyJob = _jobQueue.get();

    while (readyJob) {
        if (QThreadPool::globalInstance()->tryStart(readyJob)) {
            _jobQueue.pop();

            readyJob = _jobQueue.get();
        } else {
            // No available threads in pool
            break;
        }
    }

    if (_jobQueue.hasJobs() && !_jobQueueTimer->isActive()) {
        _jobQueueTimer->start(JOB_POLL_MS);
    } else {
        _jobQueueTimer->stop();
    }
}

void
EventHandler::processTimedJobs() {
    QList<Job *> readyTimedJobs = _timedJobs.getReadyJobs();

    if (!readyTimedJobs.isEmpty()) {
        _jobQueue << readyTimedJobs;

        processJobQueue();
    }

    if (!_timedJobs.hasJobs()) {
        _timedJobTimer->stop();
    }
}

void
EventHandler::processEvent(QSharedPointer<GatewayPayload> payload) {
    QSharedPointer<EventContext> context = QSharedPointer<EventContext>(new EventContext(payload->getD()));

    QString guildId = context->getGuildId().toString();

    if (!isGuildReady(guildId)) {
        return;
    }

    QString eventName = payload->getT().toString();

    context->setEventName(eventName);

    QSharedPointer<GuildEntity> guild = _availableGuilds[guildId];

    _jobQueue << guild->processEvent(context);

    processJobQueue();
}

void
EventHandler::guildReady(QSharedPointer<GuildEntity> guild) {
    _availableGuilds[guild->getId()] = guild;

    _timedJobs.registerTimedBindings(guild);

    if (_timedJobs.hasJobs() && !_timedJobTimer->isActive()) {
        _timedJobTimer->start(JOB_POLL_MS);
    }
}

void
EventHandler::registerTimedBinding(const QString &guildId, QSharedPointer<TimedBinding> timedBinding) {
    _timedJobs.registerTimedBinding(guildId, *timedBinding.data());

    if (_timedJobs.hasJobs() && !_timedJobTimer->isActive()) {
        _timedJobTimer->start(JOB_POLL_MS);
    }
}

void
EventHandler::reloadGuild(const EventContext &context) {
    QString guildId = context.getGuildId().toString();

    if (guildId == DEFAULT_GUILD_ID) {
        QString userId = context.getUserId().toString();

        if (userId == GuildEntity::getBotOwnerId()) {
            _timedJobTimer->stop();

            _jobQueueTimer->stop();

            for (auto guild : _availableGuilds.values()) {
                _timedJobs.clear(guild->getId());

                _jobQueue.clear(guild->getId());

                emit reloadScripts(guild);
            }
        } else {
            _logger->warning(QString("User %1 attempted to .reload all guilds but they are not Bot Owner...").arg(userId));
        }
    } else {
        _timedJobs.clear(guildId);

        _jobQueue.clear(guildId);

        emit reloadScripts(_availableGuilds[guildId]);
    }
}

void
EventHandler::displayTimedJobs(EventContext context) {
    QString guildId = context.getGuildId().toString();

    QList<TimedBinding> timedBindings = _timedJobs.getAllJobs(guildId);

    if (timedBindings.size() == 0) {
        return;
    }

    QString content = QString("Found `%1` timed jobs for GuildId: `%2`\n")
            .arg(timedBindings.size())
            .arg(guildId);

    for (int i = 0; i < timedBindings.size(); ++i) {
        TimedBinding timedBinding = timedBindings[i];

        QString jobInfo = QString("Timed Job#: `%1` => `ScriptName: %2 | FunctionName: %3 | SingleShot: %4 | Running: %5 | Remaining: %6s")
                .arg(i + 1)
                .arg(timedBinding.getScriptName())
                .arg(timedBinding.getFunctionMapping().first)
                .arg(timedBinding.isSingleShot() == true ? "true" : "false")
                .arg(timedBinding.isRunning() == true ? "true" : "false")
                .arg(timedBinding.getRemaining());

        content.append(jobInfo);

        QString description = timedBinding.getDescription();

        if (!description.isEmpty()) {
            jobInfo = QString(" | Description: %1")
                    .arg(description);

            content.append(jobInfo);
        }

        content.append("\n`");
    }

    Message message;

    message.setContent(content);

    context.setTargetPayload(message.toQJsonObject());

    _discordAPI->channelCreateMessage(SerializationUtils::toVariant(context));
}

bool
EventHandler::isGuildReady(const QString &guildId) {
    if (_availableGuilds.contains(guildId)) {
        return true;
    }

    _logger->debug(QString("Guild %1 is still initializing.").arg(guildId));

    return false;
}

int
EventHandler::getTimedJobNumber(const EventContext &context) {
    QStringList commandTokens = context.getContent().toString().split(" ");

    if (commandTokens.size() <= 1) {
        return -1;
    }

    return commandTokens[1].toInt();
}

void
EventHandler::removeTimedJobById(QSharedPointer<EventContext> context) {
    QString jobId = context->getJobId().toString();

    if (!jobId.isEmpty()) {
        _timedJobs.removeJobById(context->getGuildId().toString(), jobId);
    } else {
        _logger->debug(QString("You must specify a job id for command: %1").arg(context->getContent().toString()));
    }
}

void
EventHandler::removeTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.removeJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::restartTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.restartJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::startTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.startJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::stopTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.stopJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}


void
EventHandler::toggleCommand(const EventContext &context, CommandRestrictions::RestrictionState state) {
    QString guildId = context.getGuildId().toString();

    if (isGuildReady(guildId) && context.getArgs().size() > 2) {
        QString commandName = context.getArgs()[1].toString();

        QString targetId = context.getArgs()[2].toString();

        _availableGuilds[guildId]->toggleCommand(commandName, targetId, state);
    } else {
        _logger->debug(QString("\"%1\" requires a scriptName/commandName and user/role/channel/guild id...").arg(context.getContent().toString()));
    }
}

void
EventHandler::clear(const EventContext &context) {
    QString guildId = context.getGuildId().toString();

    int argCount = context.getArgs().size();

    if (isGuildReady(guildId) && argCount > 1) {
        QString commandName = context.getArgs()[1].toString();

        QString targetId;

        if (argCount > 2) {
            targetId = context.getArgs()[2].toString();
        }

        _availableGuilds[guildId]->clear(commandName, targetId);
    } else {
        _logger->debug(QString("\"%1\" requires a scriptName or command name...").arg(context.getContent().toString()));
    }
}


