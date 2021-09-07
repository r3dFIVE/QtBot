#include "mongofind.h"

#include "util/mongoutils.h"


const QString MongoFind::TYPE_NAME = "MongoDB";

MongoFind::MongoFind(const MongoFind &other) {
    _findArgs = other._findArgs;
}

MongoFind&
MongoFind::operator=(const MongoFind &other) {
    if (this == &other) {
        return *this;
    }

    _findArgs = mongocxx::options::find{other._findArgs};

    return *this;
}


void
MongoFind::allowDiskUse(bool allow) {
    _findArgs.allow_disk_use(allow);
}

bool
MongoFind::allowDiskUse() const {
    bool allow = false;

    auto result = _findArgs.allow_disk_use();

    if (result) {
        allow = result.get();
    }

    return allow;
}

void
MongoFind::allowPartialResults(bool allow) {
    _findArgs.allow_partial_results(allow);
}

bool
MongoFind::allowPartialResults() const {
    bool allow = false;

    auto result = _findArgs.allow_partial_results();

    if (result) {
        allow = result.get();
    }

    return allow;
}

void
MongoFind::batchSize(int size) {
    _findArgs.batch_size(size);
}

int
MongoFind::batchSize() const {
    int size = 0;

    auto result = _findArgs.batch_size();

    if (result) {
        size = result.get();
    }

    return size;
}

void
MongoFind::hint(const QJsonObject &json) {
    _findArgs.hint(mongocxx::hint{MongoUtils::toViewOrValue(json)});
}

QJsonObject
MongoFind::hint() const {
    QJsonObject json;

    auto result = _findArgs.hint();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

void
MongoFind::limit(long limit) {
    _findArgs.limit(limit);
}

long
MongoFind::limit() const {
    int64_t limit = 0;

    auto result = _findArgs.limit();

    if (result) {
        limit = result.get();
    }

    return limit;
}

void
MongoFind::max(const QJsonObject &json) {
    _findArgs.max(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFind::max() const {
    QJsonObject json;

    auto result = _findArgs.max();

    if (result) {
        json = MongoUtils::toJson(result->view());
    }

    return json;
}

void
MongoFind::maxAwaitTime(long time) {
    _findArgs.max_await_time(std::chrono::milliseconds{time});
}

long
MongoFind::maxAwaitTime() const {
    long time = 0;

    auto result = _findArgs.max_await_time();

    if (result) {
        time = result.get().count();
    }

    return time;
}

void
MongoFind::min(const QJsonObject &json) {
    _findArgs.min(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFind::min() const {
    QJsonObject json;

    auto result = _findArgs.min();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

bool
MongoFind::noCursorTimeout() const {
    bool allow = false;

    auto result = _findArgs.no_cursor_timeout();

    if (result) {
        allow = result.get();
    }

    return allow;
}

void
MongoFind::noCursorTimeout(bool timeout) {
    _findArgs.no_cursor_timeout(timeout);
}

void
MongoFind::projection(const QJsonObject &json) {
    _findArgs.projection(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFind::projection() const {
    QJsonObject json;

    auto result = _findArgs.projection();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

bool
MongoFind::returnKey() const {
    bool allow = false;

    auto result = _findArgs.return_key();

    if (result) {
        allow = result.get();
    }

    return allow;
}

void
MongoFind::returnKey(bool returnKey) {
    _findArgs.return_key(returnKey);
}

bool
MongoFind::showRecordId() const {
    bool allow = false;

    auto result = _findArgs.show_record_id();

    if (result) {
        allow = result.get();
    }

    return allow;
}

void
MongoFind::showRecordId(bool showRecordId) {
    _findArgs.show_record_id(showRecordId);
}

void
MongoFind::skip(long skip) {
    _findArgs.skip(skip);
}

long
MongoFind::skip() const {
    long skipDuration = 0;

    auto result = _findArgs.limit();

    if (result) {
        skipDuration = result.get();
    }

    return skipDuration;
}

void
MongoFind::sort(const QJsonObject &json) {
    _findArgs.sort(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFind::sort() const {
    QJsonObject json;

    auto result = _findArgs.sort();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}


mongocxx::options::find
MongoFind::get() const {
    return _findArgs;
}
