#include "eventhandler.h"

#include <QDebug>
#include <QThreadPool>

#include "util/globals.h"
#include "util/enumutils.h"
#include "botjob/botscript.h"
#include "botjob/job.h"


QString
EventHandler::parseCommandToken(const QString &message) {
    int start = -1;
    int i;

    for (i = 0; i < message.size(); i++) {
        if (start < 0 && message[i].isSpace()) {
            continue;
        } else if (start < 0 && !message[i].isSpace()) {
            start = i;
        } else if (start >= 0 && message[i].isSpace()) {
            break;
        }
    }    

    if (start >= 0) {
        return message.mid(start, i - start);
    } else {
        return QString();
    }
}

void
EventHandler::processCommands(QSharedPointer<EventContext> context) {
    QString guildId = context->getGuildId().toString();

    if (!_availableGuilds.contains(guildId)) {
        _logger->debug(QString("Guild %1 is still initializing.").arg(guildId));

        return;
    }

    QSharedPointer<GuildEntity> guild = _availableGuilds[guildId];

    context->setCommand(parseCommandToken(context->getContent().toString()));

    Job *botJob = guild->getBotJob(context);

    if (botJob) {
        _jobQueue << botJob;

        processJobQueue();
    }
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

    if (_jobQueue.hasJobs()) {
        QTimer::singleShot(1000, this, &EventHandler::processJobQueue);
    }
}

void
EventHandler::processEvent(QSharedPointer<GatewayPayload> payload) {
    GatewayEvents::Events eventType = EnumUtils::keyToValue<GatewayEvents::Events>(payload->getT());

    QSharedPointer<EventContext> context = QSharedPointer<EventContext>(new EventContext(payload->getD()));

    switch(eventType) {
    case GatewayEvents::GUILD_CREATE:
        processGuildCreate(context);
        break;
    //TODO parse message type
    case GatewayEvents::MESSAGE_CREATE:
        processCommands(context);
        break;
    case GatewayEvents::MESSAGE_UPDATE:
        processCommands(context);
        break;
    default:
        return;
    }
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

void
EventHandler::processGuildCreate(QSharedPointer<EventContext> context) {
    emit guildOnline(context->getSourcePayload()[Guild::ID].toString());
}
