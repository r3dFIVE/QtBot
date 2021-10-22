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

    bsoncxx::document::view_or_value guildDoc = buildSearchByGuildId(guildEntity->getId());

    bsoncxx::stdx::optional<bsoncxx::document::value> result;

    try {
        result = _collection.find_one(guildDoc);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Failed to execute find_one during guild init. REASON: %1").arg(e.what()));

        return;
    }

    if (result) {
        guildEntity->initRestrictionStates(MongoUtils::toJson(result.value()));
    } else {

        try {
            _collection.insert_one(guildDoc);

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

    update(restrictions, UNSET_OPERATION);
}

void
MongoManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    update(restrictions, SET_OPERATION);
}

void
MongoManager::update(QSharedPointer<CommandRestrictions> restrictions, const QString &operation) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    auto update = document{};

    update << operation.toStdString() << open_document;

    if (!restrictions->getRestrictions().isEmpty()) {
        QString targetId = restrictions->getTargetId();

        if (!targetId.isEmpty()) {
            targetId = QString(".%1").arg(targetId);
        }

        QMapIterator<QString, CommandRestrictions::RestrictionState> m_it(restrictions->getRestrictions());

        while (m_it.hasNext()) {
            m_it.next();

            update << QString("%1.%2%3")
                        .arg(GuildEntity::RESTRICTIONS)
                        .arg(m_it.key())
                        .arg(targetId)
                        .toStdString()
                  << m_it.value();
        }
    } else {
        update << GuildEntity::RESTRICTIONS.toStdString() << "";
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
