#include "mongodb.h"

#include <QJsonDocument>


MongoDB::MongoDB(const MongoDB &other) {
    _port = other._port;

    _databaseName = other._databaseName;

    _hostName = other._hostName;

    _password = other._password;

    _userName = other._userName;
}

MongoDB::MongoDB(const DatabaseContext &context) {
    _port = context.port;

    _databaseName = context.databaseName;

    _hostName = context.hostName;

    _password = context.password;

    _userName = context.userName;
}

QString
MongoDB::buildUri() {
    QString uri("mongodb://");

    bool requiresAuth = false;

    if (!_userName.isEmpty()) {
        uri.append(QString("%1:%2@").arg(_userName).arg(_password));

        requiresAuth = true;
    }

    QString hostPort = QString("%1:%2").arg(_hostName).arg(_port);

    uri.append(hostPort);

    if (requiresAuth) {
        uri.append("/?authSource=admin");
    }

    qDebug() << uri;

    return uri;
}

void
MongoDB::connect() {
    try {
        _uri = mongocxx::uri{ buildUri().toStdString() };

        _client = mongocxx::client{ _uri };

        _database = mongocxx::database { _client[_databaseName.toStdString()] };

    } catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to connect to MongoDB instance. REASON: %2").arg(e.what()));
    }
}

QSet<QString>
MongoDB::listDatabaseNames() {
    QSet<QString> databaseNames;
    try {
        for (auto name : _database.list_collection_names()) {
            databaseNames << QString::fromStdString(name);
        }
    } catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to connect to MongoDB instance. REASON: %2").arg(e.what()));
    }

    return databaseNames;
}

void
MongoDB::setCollection(const QString &collectionName) {
    try {
        _collection = _database[collectionName.toStdString()];

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to open collection: %1. REASON: %").arg(collectionName, e.what()));
    }
}

QSet<QString>
MongoDB::listCollectionNames() {
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
MongoDB::getCollectionName() {
    return QString::fromStdString(_collection.name().to_string());
}

void
MongoDB::insertOne(const QJsonObject &json) {
    try {
        QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

        _collection.insert_one(bsoncxx::from_json(jsonData.toStdString()));

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to insert record into collection. REASON: %1").arg(e.what()));
    }
}

void
MongoDB::createCollection(const QString &collectionName) {
    try {
        _database.create_collection(collectionName.toStdString());

    }  catch (const mongocxx::exception& e) {
        _logger->warning(QString("Failed to create collection: %1. REASON: %2").arg(collectionName, e.what()));
    }
}

void
MongoDB::setPort(int port) {
    _port = port;
}

int
MongoDB::getPort() {
    return _port;
}

void
MongoDB::setDatabaseName(const QString &databaseName) {
    _databaseName = databaseName;
}

QString
MongoDB::getDatabaseName() {
    return _databaseName;
}

void
MongoDB::setHostName(const QString &hostName) {
    _hostName = hostName;
}

QString
MongoDB::getHostName() {
    return _hostName;
}

void
MongoDB::setPassword(const QString &password) {
    _password = password;
}

QString
MongoDB::getPassword() {
    return _password;
}

void
MongoDB::setUserName(const QString &userName) {
    _userName = userName;
}

QString
MongoDB::getUserName() {
    return _userName;
}
