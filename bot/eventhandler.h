#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <QSqlQuery>

#include "botjob/jobqueue.h"
#include "entity/guildentity.h"
#include "payloads/gatewaypayload.h"
#include "payloads/message.h"
#include "payloads/guild.h"
#include "qml/commandfactory.h"
#include "util/settings.h"
#include "logging/logfactory.h"
#include "util/corecommand.h"

class EventHandler : public QObject
{
    Q_OBJECT

    JobQueue _jobQueue;

    QMap<QString, QSharedPointer<GuildEntity> > _availableGuilds;
    QSharedPointer<Settings> _settings;

    QString _botToken;
    QString _scriptDir;
    QSqlQuery _query;
    Logger *_logger;

    QString parseCommandToken(const QString &message);
    void processGuildCreate(QSharedPointer<EventContext> context);
    void processMessageCreate(QSharedPointer<EventContext> context);
    void processMessageUpdate(QSharedPointer<EventContext> context);
    void processCommands(QSharedPointer<EventContext> context);
    void processJobQueue();

public:
    EventHandler(QSharedPointer<Settings> settings);

signals:
    void guildOnline(const QString &guildId);
    void reloadCommands(QSharedPointer<GuildEntity> guild);

public slots:
    void processEvent(QSharedPointer<GatewayPayload> payload);
    void guildReady(QSharedPointer<GuildEntity> guild);
    void reloadAllAvailableGuilds();
    void init();
};

#endif // MESSAGEHANDLER_H
