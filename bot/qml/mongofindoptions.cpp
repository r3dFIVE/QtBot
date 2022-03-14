#include "mongofindoptions.h"

#include "util/mongoutils.h"

#include <optional>

const QString MongoFindOptions::ALLOW_DISK_USE = QString("allow_disk_use");
const QString MongoFindOptions::ALLOW_PARTIAL_RESULTS = QString("allow_partial_results");
const QString MongoFindOptions::BATCH_SIZE = QString("batch_size");
const QString MongoFindOptions::COLLATION = QString("collation");
const QString MongoFindOptions::COMMENT = QString("comment");
const QString MongoFindOptions::HINT = QString("hint");
const QString MongoFindOptions::LIMIT = QString("limit");
const QString MongoFindOptions::MAX = QString("max");
const QString MongoFindOptions::MAX_AWAIT_TIME = QString("max_await_time");
const QString MongoFindOptions::MAX_TIME = QString("max_time");
const QString MongoFindOptions::MIN = QString("min");
const QString MongoFindOptions::NO_CURSOR_TIMEOUT = QString("no_cursor_timeout");
const QString MongoFindOptions::PROJECTION = QString("projection");
const QString MongoFindOptions::RETURN_KEY = QString("return_key");
const QString MongoFindOptions::SHOW_RECORD_ID = QString("show_record_id");
const QString MongoFindOptions::SKIP = QString("skip");
const QString MongoFindOptions::SORT = QString("sort");

mongocxx::options::find
MongoFindOptions::fromJson(const QJsonObject &options) {
    mongocxx::options::find findOptions{};

    if (options.contains(ALLOW_DISK_USE)) {
        auto allow = options[ALLOW_DISK_USE].toBool();

        findOptions.allow_disk_use(allow);
    }

    if (options.contains(ALLOW_DISK_USE)) {
        auto allow = options[ALLOW_PARTIAL_RESULTS].toBool();

        findOptions.allow_partial_results(allow);
    }

    if (options.contains(BATCH_SIZE)) {
        auto size = options[BATCH_SIZE].toInt();

        findOptions.batch_size(size);
    }

    if (options.contains(COLLATION)) {
        auto collation = options[COLLATION].toObject();

        findOptions.collation(MongoUtils::toViewOrValue(collation));
    }

    if (options.contains(COMMENT)) {
        auto comment = options[COMMENT].toString();

        findOptions.comment(comment.toStdString());
    }

    if (options.contains(HINT)) {
        auto hint = options[HINT].toObject();

        findOptions.hint(mongocxx::hint{MongoUtils::toViewOrValue(hint)});
    }

    if (options.contains(LIMIT)) {
        auto limit = options[LIMIT].toInt();

        findOptions.limit(limit);
    }

    if (options.contains(MAX)) {
        auto max = options[MAX].toInt();

        findOptions.max(MongoUtils::toViewOrValue(max));
    }

    if (options.contains(MAX_AWAIT_TIME)) {
        auto time = options[MAX_AWAIT_TIME].toInt();

        findOptions.max_await_time(std::chrono::milliseconds{time});
    }

    if (options.contains(MAX_TIME)) {
        auto time = options[MAX_TIME].toInt();

        findOptions.max_time(std::chrono::milliseconds{time});
    }

    if (options.contains(MIN)) {
        auto min = options[MIN].toInt();

        findOptions.min(MongoUtils::toViewOrValue(min));
    }

    if (options.contains(NO_CURSOR_TIMEOUT)) {
        auto timeout = options[NO_CURSOR_TIMEOUT].toBool();

        findOptions.no_cursor_timeout(timeout);
    }

    if (options.contains(PROJECTION)) {
        auto projection = options[PROJECTION].toObject();

        findOptions.projection(MongoUtils::toViewOrValue(projection));
    }

    if (options.contains(RETURN_KEY)) {
        auto ret = options[RETURN_KEY].toBool();

        findOptions.return_key(ret);
    }

    if (options.contains(SHOW_RECORD_ID)) {
        auto show = options[SHOW_RECORD_ID].toBool();

        findOptions.show_record_id(show);
    }

    if (options.contains(SKIP)) {
        auto duration = options[SKIP].toInt();

        findOptions.skip(duration);
    }

    if (options.contains(SORT)) {
        auto sort = options[SORT].toObject();

        findOptions.sort(MongoUtils::toViewOrValue(sort));
    }

    return findOptions;
}

mongocxx::options::find
MongoFindOptions::fromVariant(const QVariant &options) {
    mongocxx::options::find findOptions{};

    if (options.isValid())  {
        auto find = qvariant_cast<MongoFindOptions*>(options);

        if (find) {
            findOptions = find->get();
        }
    } else {
        getLogger()->warning(QString("Failed to set Mongo Find Options: %1").arg(options.toString()));

        findOptions = mongocxx::options::find{};
    }

    return findOptions;
}

MongoFindOptions::MongoFindOptions(const MongoFindOptions &other, QObject *parent) : QObject(parent) {
    _findOptions = other._findOptions;
}

MongoFindOptions&
MongoFindOptions::operator=(const MongoFindOptions &other) {
    if (this == &other) {
        return *this;
    }

    _findOptions = other._findOptions;

    return *this;
}


void
MongoFindOptions::allowDiskUse(bool allow) {
    _findOptions.allow_disk_use(allow);
}

bool
MongoFindOptions::allowDiskUse() const {
    bool allow = false;

    auto result = _findOptions.allow_disk_use();

    if (result) {
        allow = result.value();
    }

    return allow;
}

void
MongoFindOptions::allowPartialResults(bool allow) {
    _findOptions.allow_partial_results(allow);
}

bool
MongoFindOptions::allowPartialResults() const {
    bool allow = false;

    auto result = _findOptions.allow_partial_results();

    if (result) {
        allow = result.value();
    }

    return allow;
}

void
MongoFindOptions::batchSize(int size) {
    _findOptions.batch_size(size);
}

int
MongoFindOptions::batchSize() const {
    int size = 0;

    auto result = _findOptions.batch_size();

    if (result) {
        size = result.value();
    }

    return size;
}

void
MongoFindOptions::collation(const QJsonObject &json) {
    _findOptions.collation(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFindOptions::collation() {
    return MongoUtils::toJson(_findOptions.collation().value());
}

void
MongoFindOptions::hint(const QJsonObject &json) {
    _findOptions.hint(mongocxx::hint{MongoUtils::toViewOrValue(json)});
}

QJsonObject
MongoFindOptions::hint() const {
    QJsonObject json;

    auto result = _findOptions.hint();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

void
MongoFindOptions::limit(long limit) {
    _findOptions.limit(limit);
}

long
MongoFindOptions::limit() const {
    int64_t limit = 0;

    auto result = _findOptions.limit();

    if (result) {
        limit = result.value();
    }

    return limit;
}

void
MongoFindOptions::max(const QJsonObject &json) {
    _findOptions.max(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFindOptions::max() const {
    QJsonObject json;

    auto result = _findOptions.max();

    if (result) {
        json = MongoUtils::toJson(result->view());
    }

    return json;
}

void
MongoFindOptions::maxAwaitTime(long time) {
    _findOptions.max_await_time(std::chrono::milliseconds{time});
}

long
MongoFindOptions::maxAwaitTime() const {
    long time = 0;

    auto result = _findOptions.max_await_time();

    if (result) {
        time = result.value().count();
    }

    return time;
}

void
MongoFindOptions::min(const QJsonObject &json) {
    _findOptions.min(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFindOptions::min() const {
    QJsonObject json;

    auto result = _findOptions.min();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

bool
MongoFindOptions::noCursorTimeout() const {
    bool allow = false;

    auto result = _findOptions.no_cursor_timeout();

    if (result) {
        allow = result.value();
    }

    return allow;
}

void
MongoFindOptions::noCursorTimeout(bool timeout) {
    _findOptions.no_cursor_timeout(timeout);
}

void
MongoFindOptions::projection(const QJsonObject &json) {
    _findOptions.projection(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFindOptions::projection() const {
    QJsonObject json;

    auto result = _findOptions.projection();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

bool
MongoFindOptions::returnKey() const {
    bool allow = false;

    auto result = _findOptions.return_key();

    if (result) {
        allow = result.value();
    }

    return allow;
}

void
MongoFindOptions::returnKey(bool returnKey) {
    _findOptions.return_key(returnKey);
}

bool
MongoFindOptions::showRecordId() const {
    bool allow = false;

    auto result = _findOptions.show_record_id();

    if (result) {
        allow = result.value();
    }

    return allow;
}

void
MongoFindOptions::showRecordId(bool showRecordId) {
    _findOptions.show_record_id(showRecordId);
}

void
MongoFindOptions::skip(long skip) {
    _findOptions.skip(skip);
}

long
MongoFindOptions::skip() const {
    long skipDuration = 0;

    auto result = _findOptions.limit();

    if (result) {
        skipDuration = result.value();
    }

    return skipDuration;
}

void
MongoFindOptions::sort(const QJsonObject &json) {
    _findOptions.sort(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoFindOptions::sort() const {
    QJsonObject json;

    auto result = _findOptions.sort();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}


mongocxx::options::find
MongoFindOptions::get() const {
    return _findOptions;
}
