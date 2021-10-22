#include "mongomanager.h"

#include "util/globals.h"

#include "util/mongoutils.h"
#include "mongoconnectionpool.h"

using namespace bsoncxx::builder::stream;
using namespace mongocxx;

const QString MongoManager::SET_OPERATION = "$set";
const QString MongoManager::UNSET_OPERATION = "$unset";

void
MongoManager::init() {
    try {
        if (!_instance) {
            _instance = QSharedPointer<mongocxx::instance>(new mongocxx::instance{});

            MongoConnectionPool::init(_databaseContext);
        }

        _uri = mongocxx::uri{ MongoUtils::buildUri(_databaseContext) };

        _client = mongocxx::client{ _uri };

        _database = mongocxx::database { _client[_databaseContext.databaseName.toStdString()] };

    } catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to connect to MongoDB instance. REASON: %1").arg(e.what()));
    }
}

void
MongoManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    bsoncxx::document::view_or_value doc = document{}
            << "id" << guildEntity->getId().toStdString()
        << finalize;

    bsoncxx::stdx::optional<bsoncxx::document::value> result;

    try {
        result = _collection.find_one(doc);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Failed to execute find_one during guild init. REASON: %1").arg(e.what()));

        return;
    }

    if (result) {
        guildEntity->initRestrictionStates(MongoUtils::toJson(result.value()));
    } else {

        try {
            _collection.insert_one(doc);

        } catch (mongocxx::exception &e) {
            _logger->warning(QString("Failed create command restrictions for guildID: %1, REASON: %2")
                             .arg(guildEntity->getId())
                             .arg(e.what()));
        }
    }

}

void
MongoManager::saveEvent(QSharedPointer<GatewayPayload> payload) {
    if (payload->getOp().toInt() == GatewayEvent::DISPATCH) {
        setCollection(payload->getT().toString());

        insertOne(payload->getD());
    }
}

void
MongoManager::restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    switch (restrictions->getType()) {
        case CommandRestrictions::REMOVE_ALL:
            restrictionsRemoveAll(restrictions->getGuildId());
            break;
        case CommandRestrictions::REMOVE_BY_NAME:
        case CommandRestrictions::REMOVE_BY_ID:
            update(restrictions, UNSET_OPERATION);
            break;
        default:
            break;
    }
}

void
MongoManager::restrictionsRemoveAll(const QString &guildId) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    auto remove = document{};

    remove << "$unset" << open_document;

    remove << GuildEntity::RESTRICTIONS.toStdString() << "" << close_document;

    bsoncxx::document::view_or_value value = remove << finalize;

    try {
        _collection.update_one(buildSearchByGuildId(guildId), value);

    }  catch (mongocxx::exception &e) {
        _logger->warning(QString("Failed to remove all command restrictions. REASON: %1").arg(e.what()));
    }
}

void
MongoManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {
    update(restrictions, SET_OPERATION);
}

void
MongoManager::update(QSharedPointer<CommandRestrictions> restrictions, const QString &operation) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    auto update = document{};

    update << operation.toStdString() << open_document;

    QMapIterator<QString, CommandRestrictions::RestrictionState> m_it(restrictions->getRestrictions());

    while (m_it.hasNext()) {
        m_it.next();

        QString targetId = restrictions->getTargetId();

        if (!targetId.isEmpty()) {
            targetId = QString(".%1").arg(targetId);
        }

        update << QString("%1.%2%3")
                    .arg(GuildEntity::RESTRICTIONS)
                    .arg(m_it.key())
                    .arg(targetId)
                    .toStdString()
              << m_it.value();
    }

    update << close_document;

    bsoncxx::document::view_or_value value = update << finalize;

    try {
        _collection.update_one(buildSearchByGuildId(restrictions->getGuildId()), value);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Failed to update/remove command restrictions. REASON: %1").arg(e.what()));
    }
}

void
MongoManager::setCollection(const QString &collectionName) {
    try {
        _collection = _database[collectionName.toStdString()];

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to open collection: %1. REASON: %2").arg(collectionName, e.what()));
    }
}

void
MongoManager::insertOne(const QJsonObject &json) {
    try {
        _collection.insert_one(MongoUtils::toViewOrValue(json));

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to insert record into collection. REASON: %1").arg(e.what()));
    }
}

bsoncxx::document::view_or_value
MongoManager::buildSearchByGuildId(const QString &guildId) {
    return document{}
            << "id" << guildId.toStdString()
        << finalize;
}
