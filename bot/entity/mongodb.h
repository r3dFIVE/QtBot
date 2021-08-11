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

class MongoDB
{


private:
    DatabaseContext _defaultDatabaseContext;

    static const QString MONGODB_PREFIX;

    static bool _isGlobalInit;

    bool _valid;
    int _port = 27017;
    QString _databaseName;
    QString _hostName = "localhost";
    QString _password;
    QString _userName;

    mongocxx::uri _uri;
    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _coll;

    QString buildUri();

public:
    MongoDB() {}
    MongoDB(const MongoDB &other);
    MongoDB(const DatabaseContext &context);
    ~MongoDB() {}

    static void init() {
        if (!_isGlobalInit) {
            mongocxx::instance instance{};

            _isGlobalInit = true;
        }
    }

    void saveEvent(const QString &eventJson) const;
};

#endif // MONGODB_H
