#include "mongodb.h"



MongoDB::MongoDB(const MongoDB &other) {
    _defaultDatabaseContext = other._defaultDatabaseContext;

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
