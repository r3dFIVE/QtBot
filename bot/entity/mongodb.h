#ifndef MONGODB_H
#define MONGODB_H

#include <QObject>


#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/exception/exception.hpp>

#include "botjob/databasecontext.h"

#include "imanager.h"

class MongoDB
{
    Logger *_logger = LogFactory::getLogger();

    int _port;
    QString _databaseName;
    QString _hostName;
    QString _password;
    QString _userName;

    mongocxx::uri _uri;
    mongocxx::client _client;
    mongocxx::database _database;
    mongocxx::collection _collection;

    QString buildUri();

public:
    MongoDB() {}
    MongoDB(const MongoDB &other);
    MongoDB(const DatabaseContext &context);
    ~MongoDB() {}


    int getPort();
    QString getCollectionName();
    QString getDatabaseName();
    QString getHostName();
    QString getPassword();
    QString getUserName();
    QSet<QString> listCollectionNames();
    QSet<QString> listDatabaseNames();
    void connect();
    void createCollection(const QString &collectionName);
    void insertOne(const QJsonObject &json);
    void setCollection(const QString &collectionName);
    void setPort(int port);
    void setDatabaseName(const QString &databaseName);
    void setHostName(const QString &hostName);
    void setPassword(const QString &password);
    void setUserName(const QString &userName);
};

#endif // MONGODB_H
