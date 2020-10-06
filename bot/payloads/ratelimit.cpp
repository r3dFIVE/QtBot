#include "ratelimit.h"


const QString RateLimit::GLOBAL = "global";
const QString RateLimit::MESSAGE = "message";
const QString RateLimit::RETRY_AFTER = "retry_after";

QJsonValue
RateLimit::getGlobal() const {
    return _jsonObject[GLOBAL];
}

void
RateLimit::setGlobal(const QJsonValue &global) {
    _jsonObject[GLOBAL] = global;
}

QJsonValue
RateLimit::getMessage() const {
    return _jsonObject[MESSAGE];
}

void
RateLimit::setMessage(const QJsonValue &message) {
    _jsonObject[MESSAGE] = message;
}

QJsonValue
RateLimit::getRetryAfter() const {
    return _jsonObject[RETRY_AFTER];
}

void
RateLimit::setRetryAfter(const QJsonValue &retryAfter) {
    _jsonObject[RETRY_AFTER] = retryAfter;
}
