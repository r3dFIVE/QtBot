#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>

#include "payloads/guild.h"
#include "entity/guildentity.h"

class EntityManager : public QObject
{
    Q_OBJECT
public:
    explicit EntityManager(QObject *parent = nullptr);



signals:
    void guildInitialized(QSharedPointer<GuildEntity> guildEntity);

public slots:
    void initGuild(const QString &guildId);
};

#endif // ENTITYMANAGER_H
