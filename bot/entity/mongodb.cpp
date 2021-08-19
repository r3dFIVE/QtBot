#include "mongoconnectionpool.h"
#include "mongodb.h"

#include <QJsonDocument>

Logger* MongoDB::_logger = nullptr;

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

mongocxx::uri
MongoDB::buildUri(const DatabaseContext &ctx) {
    if (!_logger) {
        _logger = LogFactory::getLogger();
    }

    QString uri("mongodb://");

    bool requiresAuth = false;

    if (!ctx.userName.isEmpty()) {
        uri.append(QString("%1:%2@").arg(ctx.userName.arg(ctx.password)));

        requiresAuth = true;
    }

    QString hostPort = QString("%1:%2").arg(ctx.hostName).arg(ctx.port);

    uri.append(hostPort);

    uri.append(QString("/?minPoolSize=%1&maxPoolSize=%2").arg(ctx.minPoolSize).arg(ctx.maxPoolSize));

    if (requiresAuth) {
        uri.append("&authSource=admin");
    }

    return mongocxx::uri{uri.toStdString()};
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
MongoDB::setCollectionName(const QString &collectionName) {
    _collectionName = collectionName.toStdString();
}

QString
MongoDB::getCollectionName() {
    return QString::fromStdString(_collectionName);
}


void
MongoDB::setDatabaseName(const QString &databaseName) {
    _databaseName = databaseName.toStdString();
}

QString
MongoDB::getDatabaseName() {
    return QString::fromStdString(_databaseName);
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

QJsonObject
MongoDB::findOne(const QString &filter) {
    auto client = MongoConnectionPool::acquire();

    auto database = (*client)[_databaseName];

    auto collection = database[_collectionName];

    auto result = collection.find_one(bsoncxx::from_json(filter.toStdString()));

    return QJsonDocument::fromJson(QString::fromStdString(bsoncxx::to_json(*result)).toUtf8()).object();
}
