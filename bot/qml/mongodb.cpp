#include "mongodb.h"

#include <QQmlEngine>

#include "mongodeleteoptions.h"
#include "mongoupdateoptions.h"
#include "mongofindoptions.h"
#include "mongoinsertoptions.h"
#include "entity/gridfsfile.h"
#include "util/mongoutils.h"
#include "util/enumutils.h"
#include "util/databasetype.h"
#include "util/serializationutils.h"

#include <payloads/attachment.h>

using namespace bsoncxx::builder::stream;

const int MongoDB::TEN_MEGABYTES = 10485760;
const std::string MongoDB::ATTACHMENTS = "ATTACHMENTS";
const std::string MongoDB::ATTACHMENTS_FILES = ATTACHMENTS + ".files";
const std::string MongoDB::ATTACHMENTS_CHUNKS = ATTACHMENTS + ".chunks";

MongoDB::MongoDB(QObject *parent) : QObject(parent) {
    _databaseContext.init();
}

MongoDB::MongoDB(const MongoDB &other, QObject *parent) : QObject(parent) {
    if (this == &other) {
        return;
    }

    _databaseContext = other._databaseContext;

    _collectionName = other._collectionName;

    _databaseName = other._databaseName;

}

MongoDB::MongoDB(const DatabaseContext &context, QObject *parent) : QObject(parent) {
    _databaseContext = context;

    _databaseName = context.databaseName.toStdString();
}

void
MongoDB::port(int port) {
    _databaseContext.port = port;
}

int
MongoDB::port() {
    return _databaseContext.port;
}

void
MongoDB::collectionName(const QString &collectionName) {
    _collectionName = collectionName.toStdString();
}

QString
MongoDB::collectionName() {
    return QString::fromStdString(_collectionName);
}

void
MongoDB::databaseName(const QString &databaseName) {
    _databaseName = databaseName.toStdString();
}

QString
MongoDB::databaseName() {
    return QString::fromStdString(_databaseName);
}

void
MongoDB::hostName(const QString &hostName) {
    _databaseContext.hostName = hostName;
}

QString
MongoDB::hostName() {
    return _databaseContext.hostName;
}

void
MongoDB::password(const QString &password) {
    _databaseContext.password = password;
}

QString
MongoDB::password() {
    return _databaseContext.password;
}

void
MongoDB::userName(const QString &userName) {
    _databaseContext.userName = userName;
}

QString
MongoDB::userName() {
    return _databaseContext.userName;
}

void
MongoDB::deleteOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::delete_options &options) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][_collectionName];

    try {
        collection.delete_one(filter, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error deleting document, reason: %1").arg(e.what()));
    }
}

void
MongoDB::deleteMany(const bsoncxx::document::view_or_value &filter, const mongocxx::options::delete_options &options) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][_collectionName];

    try {
        collection.delete_many(filter, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error deleting document, reason: %1").arg(e.what()));
    }
}

void
MongoDB::insertOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::insert &options) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][_collectionName];

    try {
        collection.insert_one(filter, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error inserting document, reason: %1").arg(e.what()));
    }
}

QJsonArray
MongoDB::find(const bsoncxx::document::view_or_value &filter, const mongocxx::options::find &options) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][_collectionName];

    QJsonArray results;

    try {
        auto cursor = collection.find(filter, options);

        for (auto doc : cursor) {
            results.push_back(MongoUtils::toJson(doc));
        }
    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error running find, reason: %1").arg(e.what()));
    }

    return results;
}

QJsonObject
MongoDB::findOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::find &options) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][_collectionName];

    QJsonObject json;

    try {
        auto result = collection.find_one(filter, options);

        if (result) {
            json = MongoUtils::toJson(result.value());
        }
    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error running findOne, reason: %1").arg(e.what()));
    }

    return json;
}

void
MongoDB::updateOne(const bsoncxx::document::view_or_value &filter,
                   const bsoncxx::document::view_or_value &update,
                   const mongocxx::options::update &options) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][_collectionName];

    try {
        collection.update_one(filter, update, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error updating document, reason: %1").arg(e.what()));
    }
}

void
MongoDB::updateMany(const bsoncxx::document::view_or_value &filter,
                    const bsoncxx::document::view_or_value &update,
                    const mongocxx::options::update &options) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][_collectionName];

    try {
        collection.update_many(filter, update, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error updating documents, reason: %1").arg(e.what()));
    }
}

QVariantList
MongoDB::findFilesByMessageId(const QString &messageId) {
    QVariantList tempFiles;

    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    auto collection = client[_databaseName][ATTACHMENTS];

    auto filter = document{} << "message_id" << messageId.toStdString() << finalize;

    auto cursor = collection.find(filter.view(), mongocxx::options::find{});


    for (auto doc : cursor) {
        QJsonObject attachmentMetadata = MongoUtils::toJson(doc);

        QString checksum = attachmentMetadata[Attachment::CHECKSUM].toString();

        QString targetFilename = attachmentMetadata[Attachment::FILENAME].toString();

        TempFile *file = findFileByChecksum(checksum, client, targetFilename);

        if (!file) {
            continue;
        }

        tempFiles << QVariant::fromValue(file);
    }

    if (tempFiles.isEmpty()) {
        _logger->debug(QString("No files found for message_id: %1. Is save_attachments enabled in settings.ini?").arg(messageId));

        return tempFiles;
    }    

    return tempFiles;
}

TempFile*
MongoDB::findFileByChecksum(const QString &checksum, mongocxx::client &client, const QString &fileName) {
    auto collection = client[_databaseName][ATTACHMENTS_FILES];

    // Use 'checksum' from ATTACHMENTS collection as filename;
    auto filter = document{} << "filename" << checksum.toStdString() << finalize;

    auto result = collection.find_one(filter.view(), mongocxx::options::find{});

    if (!result) {
        _logger->debug(QString("No files found uploaded with checksum: %1").arg(checksum));

        return nullptr;
    }

    mongocxx::options::gridfs::bucket options{};

    options.bucket_name(ATTACHMENTS);

    options.chunk_size_bytes(TEN_MEGABYTES);

    auto bucket = client[_databaseName].gridfs_bucket(options);

    bsoncxx::types::bson_value::view id = result->view()[GridFSFile::OBJECT_ID.toStdString()].get_value();

    auto downloader = bucket.open_download_stream(id);

    TempFile *tempFile = new TempFile(fileName);

    QQmlEngine::setObjectOwnership(tempFile, QQmlEngine::JavaScriptOwnership);

    auto length = downloader.file_length();

    std::vector<std::uint8_t> downloaded(length);

    downloader.read(downloaded.data(), length);

    tempFile->writeRawData(reinterpret_cast<const char*>(downloaded.data()), length);

    tempFile->close();

    return tempFile;
}

TempFile*
MongoDB::findFileByChecksum(const QString &checksum, const QString &fileName) {
    auto client = mongocxx::client{MongoUtils::buildUri(_databaseContext)};

    return findFileByChecksum(checksum, client, fileName);
}
void
MongoDB::insertOne(const QVariant &document, const QVariant &options) {
    insertOne(MongoUtils::toViewOrValue(document), MongoInsertOptions::fromVariant(options));
}

void
MongoDB::insertOne(const QVariant &document, const QJsonObject &options) {
    insertOne(MongoUtils::toViewOrValue(document), MongoInsertOptions::fromJson(options));
}

QJsonArray
MongoDB::find(const QVariant &filter, const QVariant &options) {
    return find(MongoUtils::toViewOrValue(filter), MongoFindOptions::fromVariant(options));
}

QJsonArray
MongoDB::find(const QVariant &filter, const QJsonObject &options) {
    return find(MongoUtils::toViewOrValue(filter), MongoFindOptions::fromJson(options));
}

QJsonObject
MongoDB::findOne(const QVariant &filter, const QVariant &options) {
    return findOne(MongoUtils::toViewOrValue(filter), MongoFindOptions::fromVariant(options));
}

QJsonObject
MongoDB::findOne(const QVariant &filter, const QJsonObject &options) {
    return findOne(MongoUtils::toViewOrValue(filter), MongoFindOptions::fromJson(options));
}

void
MongoDB::updateOne(const QVariant &filter, const QVariant &update, const QJsonObject &options) {
    updateOne(MongoUtils::toViewOrValue(filter),
              MongoUtils::toViewOrValue(update),
              MongoUpdateOptions::fromJson(options));
}

void
MongoDB::updateOne(const QVariant &filter, const QVariant &update, const QVariant &options) {
    updateOne(MongoUtils::toViewOrValue(filter),
              MongoUtils::toViewOrValue(update),
              MongoUpdateOptions::fromVariant(options));
}

void
MongoDB::updateMany(const QVariant &filter, const QVariant &update, const QJsonObject &options) {
    updateMany(MongoUtils::toViewOrValue(filter),
               MongoUtils::toViewOrValue(update),
               MongoUpdateOptions::fromJson(options));
}

void
MongoDB::updateMany(const QVariant &filter, const QVariant &update, const QVariant &options) {
    updateMany(MongoUtils::toViewOrValue(filter),
               MongoUtils::toViewOrValue(update),
               MongoUpdateOptions::fromVariant(options));
}

void
MongoDB::deleteOne(const QVariant &filter, const QJsonObject &options) {
    deleteOne(MongoUtils::toViewOrValue(filter), MongoDeleteOptions::fromJson(options));
}

void
MongoDB::deleteOne(const QVariant &filter, const QVariant &options) {
    deleteOne(MongoUtils::toViewOrValue(filter), MongoDeleteOptions::fromVariant(options));
}

void
MongoDB::deleteMany(const QVariant &filter, const QJsonObject &options) {
    deleteMany(MongoUtils::toViewOrValue(filter), MongoDeleteOptions::fromJson(options));
}

void
MongoDB::deleteMany(const QVariant &filter, const QVariant &options) {
    deleteMany(MongoUtils::toViewOrValue(filter), MongoDeleteOptions::fromVariant(options));
}
