#ifndef MONGODB_H
#define MONGODB_H

#include <QObject>


#include <cstdint>
#include <iostream>
#include <vector>

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

#include "botjob/databasecontext.h"

#include "imanager.h"

class MongoDB : public QObject
{
    Q_OBJECT

    static Logger *_logger;

    int _port;
    std::string _databaseName;
    std::string _collectionName;
    QString _hostName;
    QString _password;
    QString _userName;

public:
    Q_INVOKABLE MongoDB() {}
    Q_INVOKABLE MongoDB(const MongoDB &other);
    Q_INVOKABLE MongoDB(const DatabaseContext &context);
    Q_INVOKABLE ~MongoDB() {}

    static mongocxx::uri buildUri(const DatabaseContext &ctx);

    Q_INVOKABLE int getPort();
    Q_INVOKABLE QString getCollectionName();
    Q_INVOKABLE QString getDatabaseName();
    Q_INVOKABLE QString getHostName();
    Q_INVOKABLE QString getPassword();
    Q_INVOKABLE QString getUserName();
    //Q_INVOKABLE void insertOne(const QJsonObject &json);
    Q_INVOKABLE QJsonObject findOne(const QString &filter);
    Q_INVOKABLE void setPort(int port);
    Q_INVOKABLE void setDatabaseName(const QString &databaseName);
    Q_INVOKABLE void setCollectionName(const QString &collectionName);
    Q_INVOKABLE void setHostName(const QString &hostName);
    Q_INVOKABLE void setPassword(const QString &password);
    Q_INVOKABLE void setUserName(const QString &userName);
};

Q_DECLARE_METATYPE(MongoDB)

#endif // MONGODB_H
