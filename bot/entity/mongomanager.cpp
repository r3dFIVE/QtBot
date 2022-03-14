#include "gridfsfile.h"
#include "mongomanager.h"

#include "util/enumutils.h"
#include "util/mongoutils.h"
#include "payloads/user.h"

#include <QDir>
#include <QNetworkReply>
#include <QTemporaryFile>

using namespace bsoncxx::builder::stream;
using namespace mongocxx;

const int MongoManager::TEN_MEGABYTES = 10485760;
const std::string MongoManager::SET_OPERATION = "$set";
const std::string MongoManager::UNSET_OPERATION = "$unset";
const std::string MongoManager::ATTACHMENTS = "ATTACHMENTS";
const std::string MongoManager::ATTACHMENTS_FILES = ATTACHMENTS + ".files";
const std::string MongoManager::ATTACHMENTS_CHUNKS = ATTACHMENTS + ".chunks";

void
MongoManager::init() {
    try {
        if (!_instance) {
            _instance = QSharedPointer<mongocxx::instance>(new mongocxx::instance{});
        }

        _uri = mongocxx::uri{ MongoUtils::buildUri(_databaseContext) };

        _client = mongocxx::client{ _uri };

        _database = mongocxx::database { _client[_databaseContext.databaseName.toStdString()] };

        connect(&_networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(processDownload(QNetworkReply*)));

    } catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to connect to MongoDB instance. REASON: %1").arg(e.what()));
    }
}

void
MongoManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    bsoncxx::document::view_or_value guildDoc = buildSearchById(guildEntity->getId());

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

        if (!Settings::saveAttachments()) {
            return;
        }

        GatewayEvent::Event gatewayEvent = EnumUtils::keyToValue<GatewayEvent::Event>(payload->getT());

        switch (gatewayEvent) {
        case GatewayEvent::MESSAGE_CREATE:
            saveAttachments(payload);
            break;
        default:
            break;
        }
    }
}

void
MongoManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    if (restrictions->getRestrictions().isEmpty() ||
            restrictions->getRestrictions().first() == CommandRestrictions::REMOVED) {

        updateRestrictions(restrictions, UNSET_OPERATION);
    } else {
        updateRestrictions(restrictions, SET_OPERATION);
    }
}

void
MongoManager::updateRestrictions(QSharedPointer<CommandRestrictions> restrictions, const std::string &operation) {
    setCollection(GuildEntity::GUILD_RESTRICTIONS);

    auto update = document{};

    update << operation << open_document;

    if (!restrictions->getRestrictions().isEmpty()) {
        QString targetId = restrictions->getTargetId();

        if (!targetId.isEmpty()) {
            targetId = QString(".%1").arg(targetId);
        }

        QMapIterator<QString, CommandRestrictions::RestrictionState> m_it(restrictions->getRestrictions());

        while (m_it.hasNext()) {
            m_it.next();

            QString updateStr = QString("%1.%2%3")
                    .arg(GuildEntity::RESTRICTIONS)
                    .arg(m_it.key())
                    .arg(targetId);

            update << updateStr.toStdString() << m_it.value();
        }
    } else {
        update << GuildEntity::RESTRICTIONS.toStdString() << "";
    }

    update << close_document;

    bsoncxx::document::view_or_value value = update << finalize;

    try {
        _collection.update_one(buildSearchById(restrictions->getGuildId()), value);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Failed to update/remove command restrictions. REASON: %1").arg(e.what()));
    }
}

void
MongoManager::saveAttachments(QSharedPointer<GatewayPayload> payload) {
    Message message(payload->getD());

    if (message.getAttachments().isEmpty()) {
        return;
    }

    for (auto v : message.getAttachments()) {
        Attachment attachment(v.toObject());

        attachment.setMessageId(message.getId());

        attachment.setGuildId(message.getGuildId());

        attachment.setChannelId(message.getChannelId());

        User user(message.getAuthor());

        attachment.setUserId(user.getId());

        queueDownload(attachment);
    }
}

void
MongoManager::processDownload(QNetworkReply* reply) {
    QString url = reply->url().toString();

    Attachment attachment = _pendingDownloads[url];

    _pendingDownloads.remove(url);

    if (reply->error()) {
        _logger->warning(QString("Failed to download message attachment, REASON: %1").arg(reply->errorString()));

        return;
    }

    QByteArray data = reply->readAll();

    reply->deleteLater();

    QString fileChecksum = QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex();

    attachment.setChecksum(fileChecksum);

    storeAttachmentData(data, attachment);
}

QString
MongoManager::runSHA256(QTemporaryFile &file) const {
    QCryptographicHash hash(QCryptographicHash::Sha256);

    hash.addData(&file);

    return hash.result().toHex();
}

void
MongoManager::storeAttachmentData(QByteArray &data, Attachment &attachment) {
    mongocxx::options::gridfs::bucket options{};

    options.bucket_name(ATTACHMENTS);

    options.chunk_size_bytes(TEN_MEGABYTES);

    auto bucket = _database.gridfs_bucket(options);



    try {
        // We use checksum for "unique" file name
        std::string checksum = attachment.getChecksum().toString().toStdString();

        if (!isPersisted(checksum)) {
            auto uploader = bucket.open_upload_stream(checksum);

            uploader.write(reinterpret_cast<unsigned char *>(data.data()), data.length());

            auto result = uploader.close();
        }

        setCollection(QString::fromStdString(ATTACHMENTS));

        insertOne(attachment);

    }  catch (const mongocxx::exception &e) {
        LogFactory::getLogger(this)->warning(QString("Failed to store attachment data, REASON: %1").arg(e.what()));
    }
}

bool
MongoManager::isPersisted(const std::string &fileName) {
    _collection = _database[ATTACHMENTS_FILES];

    auto searchFilter = document{} << "filename" << fileName << finalize;

    try  {
        auto result = _collection.find_one(searchFilter.view());

        return result ? true : false;

    }  catch (const mongocxx::exception &e) {
        LogFactory::getLogger(this)->warning(QString("Failed to store attachment data, REASON: %1").arg(e.what()));

        return false;
    }
}

void
MongoManager::queueDownload(const Attachment &attachment)  {
    QString url = attachment.getUrl().toString();

    _networkManager.get(QNetworkRequest(url));

    _pendingDownloads[url] = attachment;
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
MongoManager::insertOne(JsonSerializable &json) {
    insertOne(json.toQJsonObject());
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
MongoManager::buildSearchById(const QString &id) {
    return document{}
            << "id" << id.toStdString()
        << finalize;
}
