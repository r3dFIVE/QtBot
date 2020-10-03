#include "eventhandler.h"

#include <QDebug>
#include <QThreadPool>

#include "util/globals.h"
#include "util/enumutils.h"
#include "botjob/botscript.h"
#include "botjob/job.h"

EventHandler::EventHandler(QSharedPointer<Settings> settings) {
    GuildEntity::setBotOwnerId(settings->value(SettingsParam::Bot::OWNER_ID).toString());

    GuildEntity::setAdminRoleName(settings->value(SettingsParam::Bot::ADMIN_ROLE_NAME).toString());

    QString defaultScheme = settings->value(SettingsParam::Bot::RESTRICTION_SCHEME).toString();

    GuildEntity::setDefaultRestrictionScheme(defaultScheme);

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
        _jobQueueTimer->start(1000);
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

    if (!_availableGuilds.contains(guildId)) {
        _logger->debug(QString("Guild %1 is still initializing.").arg(guildId));

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
    _availableGuilds[guild->id()] = guild;

    _timedJobs.registerTimedBindings(guild);

    if (_timedJobs.hasJobs() && !_timedJobTimer->isActive()) {
        _timedJobTimer->start(1000);
    }
}

void
EventHandler::registerTimedBinding(const QString &guildId, QSharedPointer<TimedBinding> timedBinding) {
    _timedJobs.registerTimedBinding(guildId, *timedBinding.data());

    if (_timedJobs.hasJobs() && !_timedJobTimer->isActive()) {
        _timedJobTimer->start(1000);
    }
}

void
EventHandler::reloadAllAvailableGuilds() {
    _timedJobTimer->stop();

    _jobQueueTimer->stop();

    _timedJobs.clear();

    _jobQueue.clear();

    for (auto guild : _availableGuilds.values()) {
        emit reloadScripts(guild);
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
                .arg(timedBinding.getReimaining());

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

int
EventHandler::getJobNumber(const EventContext &context) {
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
    int jobNumber = getJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.removeJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::resumeTimedJob(const EventContext &context) {
    int jobNumber = getJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.resumeJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::startTimedJob(const EventContext &context) {
    int jobNumber = getJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.startJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    }
}

void
EventHandler::stopTimedJob(const EventContext &context) {
    int jobNumber = getJobNumber(context);

    if (jobNumber > 0) {
       _timedJobs.stopJob(context.getGuildId().toString(), jobNumber - 1);
    } else {
        _logger->debug(QString("Invalid you must specify a valid job number for command: %1").arg(context.getContent().toString()));
    };
}



