#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>

#include "entity/guildentity.h"
#include "payloads/guild.h"
#include "payloads/gatewaypayload.h"


class EntityManager : public QObject
{
    Q_OBJECT
public:
    explicit EntityManager(QObject *parent = nullptr);

signals:
    void guildInitialized(QSharedPointer<GuildEntity> guildEntity);

public slots:
    void initGuild(QSharedPointer<GuildEntity> payload);
    void initGuildFromPayload(QSharedPointer<GatewayPayload> payload);
};

#endif // ENTITYMANAGER_H
