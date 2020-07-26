#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <QSqlQuery>

#include "util/corecommand.h"
#include "payloads/gatewaypayload.h"
#include "payloads/message.h"
#include "payloads/guild.h"
#include "qml/registrarfactory.h"
#include "util/settings.h"
#include "logging/logfactory.h"
#include "entity/guildentity.h"



class EventHandler : public QObject
{
    Q_OBJECT

    QMap<QString, QSharedPointer<GuildEntity> > _availableGuilds;
    QSharedPointer<Settings> _settings;

    QString _botToken;
    QString _scriptDir;
    QSqlQuery _query;
    Logger *_logger;

    QString parseCommandToken(QString message);
    void processGuildCreate(QSharedPointer<EventContext> context);
    void processMessageCreate(QSharedPointer<EventContext> context);

public:
    EventHandler(QSharedPointer<Settings> settings);

signals:
    void guildOnline(const QString &guildId);
    void reloadCommands(QSharedPointer<GuildEntity> guild);

public slots:
    void processEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void guildReady(QSharedPointer<GuildEntity> guild);
    void reloadAllAvailableGuilds();
    void init();
};

#endif // MESSAGEHANDLER_H
