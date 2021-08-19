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

#include "imanager.h"
#include "mongodb.h"


class MongoManager : public IManager
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    QSet<QString> _availableCollections;

    mongocxx::uri _uri;
    mongocxx::client _client;
    mongocxx::database _database;
    mongocxx::collection _collection;

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
