#include "eventhandler.h"

#include <QDebug>
#include <QThreadPool>

#include "util/globals.h"
#include "util/enumutils.h"
#include "botjob/botscript.h"
#include "botjob/job.h"


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

    _jobQueue << guild->getBotJobs(context);;

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
EventHandler::reloadAllAvailableGuilds() {
    for (auto guild : _availableGuilds.values()) {
        emit reloadCommands(guild);
    }
}
