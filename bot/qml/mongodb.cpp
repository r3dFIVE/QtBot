#include "mongodb.h"
#include "mongodeleteoptions.h"
#include "mongoupdateoptions.h"

#include "mongofindoptions.h"
#include "mongoinsertoptions.h"
#include "entity/mongoconnectionpool.h"
#include "util/mongoutils.h"

#include <util/serializationutils.h>


MongoDB::MongoDB(const MongoDB &other, QObject *parent) : QObject(parent) {
    _port = other._port;

    _databaseName = other._databaseName;

    _hostName = other._hostName;

    _password = other._password;

    _userName = other._userName;
}

MongoDB::MongoDB(const DatabaseContext &context, QObject *parent) : QObject(parent) {
    _port = context.port;

    _databaseName = context.databaseName.toStdString();

    _hostName = context.hostName;

    _password = context.password;

    _userName = context.userName;
}

void
MongoDB::port(int port) {
    _port = port;
}

int
MongoDB::port() {
    return _port;
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
    _hostName = hostName;
}

QString
MongoDB::hostName() {
    return _hostName;
}

void
MongoDB::password(const QString &password) {
    _password = password;
}

QString
MongoDB::password() {
    return _password;
}

void
MongoDB::userName(const QString &userName) {
    _userName = userName;
}

QString
MongoDB::userName() {
    return _userName;
}

void
MongoDB::deleteOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::delete_options &options) {
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

    try {
        collection.delete_one(filter, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error deleting document, reason: %1").arg(e.what()));
    }
}

void
MongoDB::deleteMany(const bsoncxx::document::view_or_value &filter, const mongocxx::options::delete_options &options) {
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

    try {
        collection.delete_many(filter, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error deleting document, reason: %1").arg(e.what()));
    }
}

void
MongoDB::insertOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::insert &options) {
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

    try {
        collection.insert_one(filter, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error inserting document, reason: %1").arg(e.what()));
    }
}

QJsonArray
MongoDB::find(const bsoncxx::document::view_or_value &filter, const mongocxx::options::find &options) {
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

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
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

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
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

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
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

    try {
        collection.update_many(filter, update, options);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error updating documents, reason: %1").arg(e.what()));
    }
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
