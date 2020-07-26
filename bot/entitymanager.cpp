#include "entitymanager.h"

EntityManager::EntityManager(QObject *parent) : QObject(parent)
{

}

void EntityManager::initGuild(const QString &guildId)
{
    QSharedPointer<GuildEntity> guild = QSharedPointer<GuildEntity>(new GuildEntity);

    guild->setId(guildId);

    //TODO add Database code here, command restrictions, etc.

    emit guildInitialized(guild);
}
