#include "mongoconnectionpool.h"

#include "util/mongoutils.h"


MongoConnectionPool* MongoConnectionPool::_mongoConnectionPool{nullptr};

Logger* MongoConnectionPool::_logger = nullptr;

QSharedPointer<mongocxx::pool> MongoConnectionPool::_pool = nullptr;

MongoConnectionPool::MongoConnectionPool(const DatabaseContext &context) {
    _pool = QSharedPointer<mongocxx::pool>(new mongocxx::pool{std::move(MongoUtils::buildUri(context))});
}

void
MongoConnectionPool::init(const DatabaseContext &ctx) {
    if (_mongoConnectionPool == nullptr) {
        _logger = LogFactory::getLogger();

        _mongoConnectionPool = new MongoConnectionPool(ctx);
    }
}

MongoClient
MongoConnectionPool::acquire() {
    return _pool->acquire();
}
