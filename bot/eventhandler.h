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

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <QSqlQuery>
#include <QTimer>

#include "botjob/jobqueue.h"
#include "entity/guildentity.h"
#include "payloads/gatewaypayload.h"
#include "payloads/message.h"
#include "payloads/guild.h"
#include "botjob/corecommand.h"
#include "util/settings.h"
#include "logging/logfactory.h"
#include "routes/discordapi.h"


class EventHandler : public QObject
{
    Q_OBJECT

    static const int JOB_POLL_MS;

    QSharedPointer<DiscordAPI> _discordAPI;
    JobQueue _jobQueue;
    QMap<QString, QSharedPointer<GuildEntity> > _availableGuilds;
    QSet<QString> _guildsWithTimedEvents;
    QSharedPointer<QTimer> _jobQueueTimer;

    Logger *_logger;

    bool isGuildReady(const QString &guildId);
    int getTimedJobNumber(const EventContext &context);
    QString getJobId(const EventContext &context);
    void processMessageCreate(QSharedPointer<EventContext> context);
    void processMessageUpdate(QSharedPointer<EventContext> context);
    void checkTimedJobs();    
    void registerTimedJobs(const QString &guildId);

signals:
    void reloadScripts(QSharedPointer<GuildEntity> guild, bool validate);

public:
    EventHandler();
    ~EventHandler();

public slots:
    void removeAllRestrictionStates(const EventContext &context);
    void updateRestrictionState(const EventContext &context, CommandRestrictions::RestrictionState state);
    void updateAllRestrictionStates(const EventContext &context, CommandRestrictions::RestrictionState state);
    void displayTimedJobs(EventContext context);
    void guildReady(QSharedPointer<GuildEntity> guild);
    void init();
    void processEvent(QSharedPointer<GatewayPayload> payload);
    void processJobQueue();
    void reloadGuild(const EventContext &context);
    void registerTimedBinding(const QString &guildId, QSharedPointer<TimedBinding> timedBinding);
    void removeTimedJob(const EventContext &context);
    void removeTimedJobById(QSharedPointer<EventContext> context);
    void restartTimedJob(const EventContext &context);
    void startTimedJob(const EventContext &context);
    void stopTimedJob(const EventContext &context);
    void shutDown(const EventContext &context);
};

#endif // MESSAGEHANDLER_H
