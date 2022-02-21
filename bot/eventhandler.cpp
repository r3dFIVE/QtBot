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

#include "util/enumutils.h"
#include "botjob/botscript.h"
#include "botjob/job.h"


const int EventHandler::JOB_POLL_MS = 1000;


EventHandler::EventHandler() {
    GuildEntity::setBotOwnerId(Settings::ownerId());

    GuildEntity::setAdminRoleName(Settings::adminRoleName());

    GuildEntity::setDefaultRestrictionState(Settings::restrictionState());

    _discordAPI = QSharedPointer<DiscordAPI>(new DiscordAPI);
}

void
EventHandler::init() {
    _logger = LogFactory::getLogger();

    _jobQueueTimer = QSharedPointer<QTimer>(new QTimer);

    _jobQueueTimer->setInterval(JOB_POLL_MS);

    connect(_jobQueueTimer.data(), &QTimer::timeout, this, &EventHandler::processJobQueue);
}

void
EventHandler::processJobQueue() {
    checkTimedJobs();

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

    qDebug() << "hello";

    if ((_jobQueue.hasJobs() || _guildsWithTimedEvents.size() > 0)) {
        if(!_jobQueueTimer->isActive()) {
            _jobQueueTimer->start();
        }
    } else {
        _jobQueueTimer->stop();
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

    if (eventName.contains("MESSAGE") && context->getMessageId().toString().isEmpty()) {
        context->setMessageId(context->getSourcePayload()[EventContext::ID].toString());
    }

    QSharedPointer<GuildEntity> guild = _availableGuilds[guildId];

    _jobQueue << guild->processEvent(context);

    processJobQueue();
}

void
EventHandler::guildReady(QSharedPointer<GuildEntity> guild) {
    _availableGuilds[guild->getId()] = guild;    

    guild->initTimedJobs();

    registerTimedJobs(guild->getId());
}

void
EventHandler::registerTimedJobs(const QString &guildId) {
    if (_availableGuilds[guildId]->hasTimedJobs()) {
        if(!_jobQueueTimer->isActive()) {
            _jobQueueTimer->start();
        }

        _guildsWithTimedEvents << guildId;
    }
}

void
EventHandler::registerTimedBinding(const QString &guildId, QSharedPointer<TimedBinding> timedBinding) {
    _availableGuilds[guildId]->addTimedBinding(*timedBinding, false);
}

void
EventHandler::reloadGuild(const EventContext &context) {
    QString guildId = context.getGuildId().toString();

    if (guildId == GuildEntity::DEFAULT_GUILD_ID) {
        QString userId = context.getUserId().toString();

        if (userId == GuildEntity::getBotOwnerId()) {

            _jobQueueTimer->stop();

            bool validate = true;

            for (auto guild : _availableGuilds.values()) {

                _jobQueue.clear(guild->getId());

                emit reloadScripts(guild, validate);

                if (validate) {
                    validate = false; // only validate once.
                }
            }
        } else {
            _logger->warning(QString("User %1 attempted to .reload all guilds but they are not Bot Owner...").arg(userId));
        }
    } else {
        _jobQueue.clear(guildId);

        emit reloadScripts(_availableGuilds[guildId], true);
    }
}

void
EventHandler::displayTimedJobs(EventContext context) {
    QString guildId = context.getGuildId().toString();

    QList<TimedBinding> timedBindings = _availableGuilds[guildId]->getTimedBindings();

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
    if (context.getArgs().size() <= 1) {
        return -1;
    }

    return context.getArgs()[1].toString().toInt();;
}

void
EventHandler::checkTimedJobs() {
    QSetIterator<QString> it(_guildsWithTimedEvents);

    while (it.hasNext()) {
        QString guildId = it.next();

        if (_availableGuilds[guildId]->hasTimedJobs()) {
            _jobQueue << _availableGuilds[guildId]->getReadyTimedJobs();
        } else {
            _guildsWithTimedEvents.remove(guildId);
        }
    }
}

void
EventHandler::removeTimedJobById(QSharedPointer<EventContext> context) {
    QString jobId = context->getJobId().toString();

    QString guildId = context->getGuildId().toString();

    if (!jobId.isEmpty()) {
        _availableGuilds[guildId]->removeTimedJobById(jobId);
    } else {
        _logger->debug(QString("You must specify a job id for command: %1").arg(context->getContent().toString()));
    }
}

void
EventHandler::removeTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    QString guildId = context.getGuildId().toString();

    if (jobNumber > 0) {
       _availableGuilds[guildId]->removeTimedJob(jobNumber - 1);
    } else {
        _logger->debug(QString("You must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::restartTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    QString guildId = context.getGuildId().toString();

    if (jobNumber > 0) {
       _availableGuilds[guildId]->restartTimedJob(jobNumber - 1);
    } else {
        _logger->debug(QString("You must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::startTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    QString guildId = context.getGuildId().toString();

    if (jobNumber > 0) {
       _availableGuilds[guildId]->startTimedJob(jobNumber - 1);
    } else {
        _logger->debug(QString("You must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::stopTimedJob(const EventContext &context) {
    int jobNumber = getTimedJobNumber(context);

    QString guildId = context.getGuildId().toString();

    if (jobNumber > 0) {
       _availableGuilds[guildId]->stopTimedJob(jobNumber - 1);
    } else {
        _logger->debug(QString("You must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::updateRestrictionState(const EventContext &context, CommandRestrictions::RestrictionState state) {
    QString guildId = context.getGuildId().toString();

    if (isGuildReady(guildId) && context.getArgs().size() > 1) {
        QString commandName = context.getArgs()[1].toString();

        QString targetId;

        if (context.getArgs().size() > 2) {
            targetId = context.getArgs()[2].toString();
        } else {
            targetId = GuildEntity::GUILD_ID_ALIAS;
        }

        _availableGuilds[guildId]->updateRestrictionStates(commandName, targetId, state);

        registerTimedJobs(guildId);
    } else {
        _logger->debug(QString("You must specify at least a command name and optional id: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::updateAllRestrictionStates(const EventContext &context, CommandRestrictions::RestrictionState state) {
    QString guildId = context.getGuildId().toString();

    if (isGuildReady(guildId)) {
        QString targetId;

        if (context.getArgs().size() > 2) {
            targetId = context.getArgs()[2].toString();
        } else {
            targetId = GuildEntity::GUILD_ID_ALIAS;
        }

        _availableGuilds[guildId]->updateRestrictionStates(QString(), targetId, state);

        registerTimedJobs(guildId);
    }
}

void
EventHandler::removeAllRestrictionStates(const EventContext &context) {
    QString guildId = context.getGuildId().toString();

    if (isGuildReady(guildId)) {
         _availableGuilds[guildId]->removeAllRestrictionStates();
    }
}
