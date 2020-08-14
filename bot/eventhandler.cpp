#include "eventhandler.h"

#include <QDebug>
#include <QThreadPool>

#include "util/globals.h"
#include "util/enumutils.h"
#include "botjob/botscript.h"
#include "botjob/job.h"


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

    if (_jobQueue.hasJobs()) {
        QTimer::singleShot(1000, this, &EventHandler::processJobQueue);
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

    QList<Job *> botJobs = guild->getBotJobs(context);

    _jobQueue << botJobs;

    processJobQueue();
}

void
EventHandler::guildReady(QSharedPointer<GuildEntity> guild) {
    _availableGuilds[guild->id()] = guild;
}

void
EventHandler::reloadAllAvailableGuilds() {
    for (auto guild : _availableGuilds.values()) {
        emit reloadCommands(guild);
    }
}
