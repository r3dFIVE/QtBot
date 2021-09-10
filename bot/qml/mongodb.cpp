#include "mongodb.h"

#include "mongofind.h"
#include "mongoinsert.h"
#include "entity/mongoconnectionpool.h"
#include "util/mongoutils.h"


MongoDB::MongoDB(const MongoDB &other) {
    _port = other._port;

    _databaseName = other._databaseName;

    _hostName = other._hostName;

    _password = other._password;

    _userName = other._userName;
}

MongoDB::MongoDB(const DatabaseContext &context) {
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
MongoDB::insertOne(const QVariant &document, const QVariant &args) {
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

    try {
        auto doc = MongoUtils::fromVariant(document);

        auto insertArgs = parseInsertOpts(args);

        collection.insert_one(doc, insertArgs);

    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error running find, reason: %1").arg(e.what()));
    }

}

QJsonArray
MongoDB::find(const QVariant &filter, const QVariant &args) {
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

    QJsonArray results;

    try {
        auto searchFilter = MongoUtils::fromVariant(filter);

        auto findArgs = parseFindOpts(args);

        auto cursor = collection.find(searchFilter.view(), findArgs);

        for(auto doc : cursor) {
            results.push_back(MongoUtils::toJson(doc));
        }
    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error running find, reason: %1").arg(e.what()));
    }

    return results;
}

mongocxx::options::insert
MongoDB::parseInsertOpts(const QVariant &opts) {
    mongocxx::options::insert insertOpts{};

    if (opts.isValid())  {
        auto insert = qvariant_cast<MongoInsert*>(opts);

        if (insert) {
            insertOpts = insert->get();
        }
    } else {
        insertOpts = mongocxx::options::insert{};
    }

    return insertOpts;
}

mongocxx::options::find
MongoDB::parseFindOpts(const QVariant &args) {
    mongocxx::options::find findArgs{};

    if (args.isValid())  {
        auto find = qvariant_cast<MongoFind*>(args);

        if (find) {
            findArgs = find->get();
        }
    } else {
        findArgs = mongocxx::options::find{};
    }

    return findArgs;
}

QJsonObject
MongoDB::findOne(const QVariant &filter, const QVariant &args) {
    auto client = MongoConnectionPool::acquire();

    auto collection = (*client)[_databaseName][_collectionName];

    QJsonObject json;

    try {
        auto findArgs = parseFindOpts(args);

        auto searchFilter = MongoUtils::fromVariant(filter);

        auto result = collection.find_one(searchFilter.view(), findArgs);

        if (result) {
            json = MongoUtils::toJson(result.get());
        }
    } catch (mongocxx::exception &e) {
        _logger->warning(QString("Error running findOne, reason: %1").arg(e.what()));
    }

    return json;
}
