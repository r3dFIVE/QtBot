#ifndef MONGOCONNECTIONPOOL_H
#define MONGOCONNECTIONPOOL_H

#include <QMutex>
#include <QSharedPointer>

#ifndef Q_MOC_RUN

#include <mongocxx/instance.hpp>
#include <mongocxx/logger.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>

#endif

#include "botjob/databasecontext.h"
#include "logging/logfactory.h"
#include "util/settings.h"

using MongoClient = mongocxx::pool::entry;

class MongoConnectionPool
{
    static Logger *_logger;

    static QSharedPointer<mongocxx::pool> _pool;
    static MongoConnectionPool* _mongoConnectionPool;
    static QMutex _mutex;

protected:
    MongoConnectionPool(const DatabaseContext &context);

public:
    MongoConnectionPool(const MongoConnectionPool &other) = delete;
    void operator=(const MongoConnectionPool &) = delete;

    static void init(const DatabaseContext &context);
    static MongoClient acquire();
};

#endif // MONGOCONNECTIONPOOL_H
