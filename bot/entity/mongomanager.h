#ifndef MONGOMANAGER_H
#define MONGOMANAGER_H

#include <QObject>

#ifndef Q_MOC_RUN

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/exception/exception.hpp>

#endif

#include "idbmanager.h"
#include "qml/mongodb.h"


class MongoManager : public IDBManager
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    QSet<QString> _availableCollections;
    QSharedPointer<mongocxx::instance> _instance;

    mongocxx::client _client;
    mongocxx::collection _collection;
    mongocxx::database _database;

    mongocxx::uri _uri;

    QString getCollectionName();
    QSet<QString> listCollectionNames();
    QSet<QString> listDatabaseNames();
    void createCollection(const QString &collectionName);
    void insertOne(const QJsonObject &json);
    void setCollection(const QString &collectionName);

public:

    MongoManager(DatabaseContext context) {
        _databaseContext = context;
    }

    void initGuild(QSharedPointer<GuildEntity> guildEntity) override;
    void init() override;
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) override;
    void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) override;
    void saveEvent(QSharedPointer<GatewayPayload> payload) override;
};

#endif // MONGOMANAGER_H