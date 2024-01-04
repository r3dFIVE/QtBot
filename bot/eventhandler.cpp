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

#include "bot.h"
#include "eventhandler.h"

#include <QDebug>
#include <QThreadPool>
#include <QTimeZone>

#include "botjob/botscript.h"
#include "botjob/job.h"
#include "payloads/channel.h"
#include "payloads/guildmember.h"
#include "payloads/user.h"



const int EventHandler::JOB_POLL_MS = 1000;

EventHandler::EventHandler() {
    GuildEntity::setBotOwnerId(Settings::ownerId());

    GuildEntity::setAdminRoleName(Settings::adminRoleName());

    GuildEntity::setDefaultRestrictionState(Settings::restrictionState());

    _discordAPI = QSharedPointer<DiscordAPI>(new DiscordAPI);

    _botOnlineEpochSeconds = QDateTime::currentSecsSinceEpoch();
}

void
EventHandler::init() {
    _logger = LogFactory::getLogger(this);

    _jobQueueTimer = QSharedPointer<QTimer>(new QTimer);

    _jobQueueTimer->setInterval(JOB_POLL_MS);

    connect(_jobQueueTimer.data(), &QTimer::timeout, this, &EventHandler::processJobQueue);
}

EventHandler::~EventHandler() {
    _jobQueueTimer->stop();
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

    if ((_jobQueue.hasJobs() || _guildsWithTimedEvents.size() > 0)) {
        if(!_jobQueueTimer->isActive()) {
            _jobQueueTimer->start();
        }
    } else {
        _jobQueueTimer->stop();
    }
}

void
EventHandler::processEvent(GatewayEvent::Event event, QSharedPointer<GatewayPayload> payload) {
    QSharedPointer<EventContext> context = QSharedPointer<EventContext>(new EventContext(payload->getD()));

    QString guildId = context->getGuildId().toString();

    if (!isGuildReady(guildId)) {
        return;
    }   

    switch (event) {
    case GatewayEvent::MESSAGE_CREATE:
    case GatewayEvent::MESSAGE_DELETE:
    case GatewayEvent::MESSAGE_DELETE_BULK:
    case GatewayEvent::MESSAGE_REACTION_ADD:
    case GatewayEvent::MESSAGE_REACTION_REMOVE:
    case GatewayEvent::MESSAGE_REACTION_REMOVE_ALL:
    case GatewayEvent::MESSAGE_UPDATE:
        if (context->getMessageId().toString().isEmpty()) {
            context->setMessageId(context->getSourcePayload()[EventContext::ID].toString());
        }
        break;
    case GatewayEvent::GUILD_MEMBER_UPDATE: {
        User user(context->getSourcePayload()[GuildMember::USER].toObject());
        _activeHelpByUserId.remove(user.getId().toString());
        break;
    }
    default:
        break;
    }

    context->setEventName(payload->getT().toString());

    _jobQueue << _availableGuilds[guildId]->processEvent(context);

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
    BotScript *botScript = qobject_cast<BotScript*>(timedBinding->getFunctionMapping().second);

    _availableGuilds[guildId]->addTimedBinding(botScript, timedBinding, false);

    registerTimedJobs(guildId);
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

                _activeHelpByUserId.clear();

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

        // Clear any active help for that guild, might be stale.
        for (auto& userId : _activeHelpByUserId.keys()) {
            if (_activeHelpByUserId[userId]->getGuildId() == guildId) {
                _activeHelpByUserId.remove(userId);
            }
        }

        emit reloadScripts(_availableGuilds[guildId], true);
    }
}

void
EventHandler::displayTimedJobs(EventContext context) {
    QString guildId = context.getGuildId().toString();

    QList<QSharedPointer<TimedBinding>> timedBindings = _availableGuilds[guildId]->getTimedBindings();

    if (timedBindings.size() == 0) {
        return;
    }

    QString content = QString("Found `%1` timed jobs for GuildId: `%2`\n")
            .arg(timedBindings.size())
            .arg(guildId);

    for (int i = 0; i < timedBindings.size(); ++i) {
        TimedBinding timedBinding = *timedBindings[i];

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

        if (context.getArgs().size() > 1) {
            targetId = context.getArgs()[1].toString();
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

void
EventHandler::shutDown(const EventContext &context) {
    if (context.getUserId() == Settings::ownerId()) {
        _logger->info(Bot::GOODBYE);

        QCoreApplication::quit();
    }
}

Embed
EventHandler::getHelpPage(const EventContext &context)  {
    QString userId = context.getUserId().toString();

    QString guildId = context.getGuildId().toString();

    QString channelId = context.getChannelId().toString();

    if (!_activeHelpByUserId.contains(userId) ) {

        // UserHelp::HELP_COMMAND was called without an active help for userId
        if (guildId != GuildEntity::DEFAULT_GUILD_ID) {
            _activeHelpByUserId.insert(userId, _availableGuilds[guildId]->getUserHelp(context));

        } else {

            QString errorString = QString("Must use `%1` from a regular channel first")
                    .arg(UserHelp::HELP_COMMAND);

            _logger->warning(QString("%1, userId: %2")
                             .arg(errorString)
                             .arg(userId));

            return Embed(UserHelp::INVALID_HELP, QString("%1%2")
                         .arg(errorString)
                         .arg(UserHelp::HELP_USAGE));
        }

    }  else if (guildId != GuildEntity::DEFAULT_GUILD_ID && _activeHelpByUserId[userId]->getChannelId() != channelId) {
        // .help was called from a new channel, cache new UserHelp for channel.
        _activeHelpByUserId.insert(userId, _availableGuilds[guildId]->getUserHelp(context));
    }

    QString pageName;

    int pageNum = 0;

    bool ok;

    if (context.getArgs().size() == 2) {
        QString arg = context.getArgs()[1].toString();

        pageNum = arg.toInt(&ok);

        if (!ok) {
            pageNum = 0;

            pageName = arg;
        }

    } else if (context.getArgs().size() > 2) {
        pageName = context.getArgs()[1].toString();

        QString pageNumArg = context.getArgs()[2].toString();

        pageNum = pageNumArg.toInt(&ok);

        if (!ok) {
            _logger->warning(QString("TODO Add help page correct usage"));
        }
    }

    pageNum = pageNum > 0 ? pageNum - 1 : pageNum;

    return _activeHelpByUserId[userId]->getHelpPage(pageName, pageNum);
}

const QString
EventHandler::getDmChannel(EventContext context) {
    QString userId = context.getUserId().toString();

    if (!_dmChannelByUserId.contains(userId)) {
        QJsonObject payload;

        payload[EventContext::RECIPIENT_ID] = userId;

        context.setTargetPayload(payload);

        SerializationUtils::fromVariant(context, _discordAPI->userCreateDm(SerializationUtils::toVariant(context)));

        Channel dmChannel(context.getSourcePayload());

        _dmChannelByUserId.insert(userId, new QString(dmChannel.getId().toString()));
    }

    return *_dmChannelByUserId[userId];
}

void
EventHandler::getHelp(EventContext context) {
    Message message;

    message.setEmbed(getHelpPage(context).object());

    context.setTargetPayload(message.object());

    context.setChannelId(getDmChannel(context)); // Reply to the user DM channel instead of spamming regular channels

    _discordAPI->channelCreateMessage(SerializationUtils::toVariant(context));
}

void
EventHandler::getUptime(EventContext context) {
    qint64 seconds = QDateTime::currentSecsSinceEpoch() - _botOnlineEpochSeconds;
    qint64 minutes =  seconds / 60;
    qint64 hours = minutes / 60;
    qint64 days = hours / 24;
    minutes = minutes % 60;
    seconds = seconds % 60;
    hours = hours % 24;

    QString daysHoursMinutesSeconds = QString("```yaml\n%1d %2h %3m %4s```")
            .arg(days)
            .arg(hours)
            .arg(minutes)
            .arg(seconds);

    QDateTime botOnlineDateTime = QDateTime::fromTime_t(_botOnlineEpochSeconds).toUTC();

    EmbedFooter footer(botOnlineDateTime.toString(), "");

    Embed embed("", daysHoursMinutesSeconds);

    embed.setFooter(footer.object());

    Message message;

    message.setEmbed(embed.object());

    context.setTargetPayload(message.object());

    _discordAPI->channelCreateMessage(SerializationUtils::toVariant(context));
}
