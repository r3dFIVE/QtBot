#include "eventhandler.h"

#include <QJsonDocument>
#include <QMetaEnum>
#include <QDebug>
#include <QMap>
#include <QSqlDatabase>
#include <QtSql>

#include "util/globals.h"
#include "util/enumutils.h"
#include "qml/botscript.h"
#include "botjob/job.h"


EventHandler::EventHandler(QSharedPointer<Settings> settings) {
    _settings = settings;
    _logger = LogFactory::getLogger();
}


void
EventHandler::init() {

}

QString
EventHandler::parseCommandToken(QString message) {
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
EventHandler::processMessageCreate(QSharedPointer<EventContext> context) {
    processPossibleCommands(context);

    // TODO event binding logic
}

void
EventHandler::processMessageUpdate(QSharedPointer<EventContext> context) {
    processPossibleCommands(context);

    // TODO event binding logic
}

void
EventHandler::processPossibleCommands(QSharedPointer<EventContext> context) {
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

        Job *readyJob = _jobQueue.get();

        while (readyJob) {
            if (QThreadPool::globalInstance()->tryStart(readyJob)) {
                _jobQueue.pop();

                readyJob = _jobQueue.get();
            } else {
                break;
            }
        }
    }
}

void
EventHandler::processEvent(QSharedPointer<GatewayPayload> payload) {

    int eventType = EnumUtils::keyToValue<GatewayEvents::Events>(payload->getT().toInt());

    QSharedPointer<EventContext> context = QSharedPointer<EventContext>(new EventContext(payload->getD()));

    switch(eventType) {
    case GatewayEvents::GUILD_CREATE:
        processGuildCreate(context);
        break;
    //TODO parse message type
    case GatewayEvents::MESSAGE_CREATE:
        processMessageCreate(context);
        break;
    case GatewayEvents::MESSAGE_UPDATE:
        processMessageCreate(context);
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

