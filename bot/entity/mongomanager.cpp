#include "mongomanager.h"

#include "util/globals.h"

void
MongoManager::init() {
    _mongoDB = QSharedPointer<MongoDB>(new MongoDB(_databaseContext));

    _mongoDB->connect();

    for (auto name : _mongoDB->listCollectionNames()) {
        _availableCollections << name;
    }

    qDebug() << _availableCollections;
}

void
MongoManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {

}

void
MongoManager::saveEvent(QSharedPointer<GatewayPayload> payload) {
    if (payload->getOp().toInt() == GatewayEvent::DISPATCH) {
        QString collectionName = payload->getT().toString();

        if (!_availableCollections.contains(collectionName)) {
            _mongoDB->createCollection(collectionName);

            _availableCollections << collectionName;
        }

        _mongoDB->setCollection(collectionName);

        _mongoDB->insertOne(payload->getD());
    }
}

void
MongoManager::restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) {

}

void
MongoManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {

}

