#ifndef MONGOMANAGER_H
#define MONGOMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

#ifndef Q_MOC_RUN

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/types/bson_value/view.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/exception/exception.hpp>

#endif

#include "idbmanager.h"
#include "payloads/attachment.h"


class MongoManager : public IDBManager
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);

    QSet<QString> _availableCollections;
    QSharedPointer<mongocxx::instance> _instance;
    QNetworkAccessManager _networkManager;
    QMap<QString, Attachment> _pendingDownloads;

    mongocxx::client _client;
    mongocxx::collection _collection;
    mongocxx::database _database;
    mongocxx::uri _uri;


    bsoncxx::document::view_or_value buildSearchById(const QString &guildId);
    QString getCollectionName() const;
    QString runSHA256(QTemporaryFile &file) const;
    bool isPersisted(const std::string &fileName);
    void createCollection(const QString &collectionName);
    void insertOne(const QJsonObject &json);
    void insertOne(JsonSerializable &json);
    void setCollection(const QString &collectionName);
    void updateRestrictions(QSharedPointer<CommandRestrictions> restrictions, const std::string &operation);
    void restrictionsRemoveAll(const QString &guildId);
    void saveAttachments(QSharedPointer<GatewayPayload> payload);
    void queueDownload(const Attachment &attachment);
    void storeAttachmentData(QByteArray &data, Attachment &attachment);


public:

    static const int TEN_MEGABYTES;
    static const std::string SET_OPERATION;
    static const std::string UNSET_OPERATION;
    static const std::string ATTACHMENTS;
    static const std::string ATTACHMENTS_FILES;
    static const std::string ATTACHMENTS_CHUNKS;

    MongoManager(DatabaseContext context, QObject *parent = nullptr) : IDBManager(parent) {
        _databaseContext = context;
    }

    void initGuild(QSharedPointer<GuildEntity> guildEntity) override;
    void init() override;
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) override;
    void saveEvent(QSharedPointer<GatewayPayload> payload) override;

private slots:
    void processDownload(QNetworkReply* reply);

};

#endif // MONGOMANAGER_H
