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

    QSharedPointer<DiscordAPI> _discordAPI;
    JobQueue _jobQueue;
    QMap<QString, QSharedPointer<GuildEntity> > _availableGuilds;
    QSharedPointer<QTimer> _timedJobTimer;
    QSharedPointer<QTimer> _jobQueueTimer;
    TimedJobs _timedJobs;

    Logger *_logger;

    int getJobNumber(const EventContext &context);
    void processMessageCreate(QSharedPointer<EventContext> context);
    void processMessageUpdate(QSharedPointer<EventContext> context);

signals:
    void reloadScripts(QSharedPointer<GuildEntity> guild);

public:
    EventHandler(QSharedPointer<Settings> settings);

public slots:
    void displayTimedJobs(EventContext context);
    void guildReady(QSharedPointer<GuildEntity> guild);
    void init();
    void processEvent(QSharedPointer<GatewayPayload> payload);
    void processJobQueue();
    void processTimedJobs();
    void reloadAllAvailableGuilds();
    void registerTimedBinding(const QString &guildId, QSharedPointer<TimedBinding> timedBinding);
    void removeTimedJob(const EventContext &context);
    void resumeTimedJob(const EventContext &context);
    void startTimedJob(const EventContext &context);
    void stopTimedJob(const EventContext &context);
};

#endif // MESSAGEHANDLER_H
