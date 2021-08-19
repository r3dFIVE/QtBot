#include "mongomanager.h"

#include "util/globals.h"

void
MongoManager::init() {
    try {
        _uri = mongocxx::uri{ MongoDB::buildUri(_databaseContext) };

        _client = mongocxx::client{ _uri };

        _database = mongocxx::database { _client[_databaseContext.databaseName.toStdString()] };

    } catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to connect to MongoDB instance. REASON: %1").arg(e.what()));
    }

    for (auto name : listCollectionNames()) {
        _availableCollections << name;
    }
}

void
MongoManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {

}

void
MongoManager::saveEvent(QSharedPointer<GatewayPayload> payload) {
    if (payload->getOp().toInt() == GatewayEvent::DISPATCH) {
        QString collectionName = payload->getT().toString();

        if (!_availableCollections.contains(collectionName)) {
            createCollection(collectionName);

            _availableCollections << collectionName;
        }

        setCollection(collectionName);

        insertOne(payload->getD());
    }
}

void
MongoManager::restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) {

}

void
MongoManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {

}

QSet<QString>
MongoManager::listDatabaseNames() {
    QSet<QString> databaseNames;

    try {
        for (auto name : _database.list_collection_names()) {
            databaseNames << QString::fromStdString(name);
        }
    } catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to list database names. REASON: %1").arg(e.what()));
    }

    return databaseNames;
}

void
MongoManager::setCollection(const QString &collectionName) {
    try {
        _collection = _database[collectionName.toStdString()];

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to open collection: %1. REASON: %2").arg(collectionName, e.what()));
    }
}

QSet<QString>
MongoManager::listCollectionNames() {
    QSet<QString> collectionNames;

    try {
        for (auto name : _database.list_collection_names()) {
            collectionNames << QString::fromStdString(name);
        }
    } catch(const mongocxx::exception& e) {
        _logger->warning(QString("Failed to list collection names. REASON: %1").arg(e.what()));
    }

    return collectionNames;
}

QString
MongoManager::getCollectionName() {
    return QString::fromStdString(_collection.name().to_string());
}

void
MongoManager::insertOne(const QJsonObject &json) {
    try {
        QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

        _collection.insert_one(bsoncxx::from_json(jsonData.toStdString()));

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to insert record into collection. REASON: %1").arg(e.what()));
    }
}

void
MongoManager::createCollection(const QString &collectionName) {
    try {
        _database.create_collection(collectionName.toStdString());

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to create collection: %1. REASON: %2").arg(collectionName, e.what()));
    }
}
