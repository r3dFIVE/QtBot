#include "entitymanager.h"


EntityManager::EntityManager(QObject *parent) : QObject(parent)
{

}

void
EntityManager::initGuildFromPayload(QSharedPointer<GatewayPayload> payload) {
    Guild jsonGuild(payload->getD());

    QSharedPointer<GuildEntity> guildEntity = QSharedPointer<GuildEntity>(new GuildEntity(jsonGuild));

    Guild guild(payload->getD());

    guildEntity->setId(guild.getId().toString());

    initGuild(guildEntity);
}

void
EntityManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {


    //TODO add Database code here, command restrictions, etc.

    emit guildInitialized(guildEntity);
}
