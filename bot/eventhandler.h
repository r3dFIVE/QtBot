#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <QSqlQuery>
#include <QTimer>


#include "botjob/jobqueue.h"
#include "botjob/timedjobs.h"
#include "entity/guildentity.h"
#include "payloads/gatewaypayload.h"
#include "payloads/message.h"
#include "payloads/guild.h"
#include "botjob/scriptbuilder.h"
#include "botjob/corecommand.h"
#include "util/settings.h"
#include "logging/logfactory.h"

class EventHandler : public QObject
{
    Q_OBJECT

    JobQueue _jobQueue;
    QMap<QString, QSharedPointer<GuildEntity> > _availableGuilds;
    QSharedPointer<QTimer> _timedJobTimer;
    QSharedPointer<QTimer> _jobQueueTimer;
    TimedJobs _timedJobs;

    Logger *_logger;

    void processMessageCreate(QSharedPointer<EventContext> context);
    void processMessageUpdate(QSharedPointer<EventContext> context);


signals:
    void reloadCommands(QSharedPointer<GuildEntity> guild);

public slots:
    void guildReady(QSharedPointer<GuildEntity> guild);
    void init();
    void processEvent(QSharedPointer<GatewayPayload> payload);
    void reloadAllAvailableGuilds();
    void processJobQueue();
    void processTimedJobs();
};

#endif // MESSAGEHANDLER_H
