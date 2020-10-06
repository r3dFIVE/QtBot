#ifndef RATELIMIT_H
#define RATELIMIT_H

#include <QObject>

#include "jsonserializable.h"


class RateLimit : public JsonSerializable
{
public:
    static const QString GLOBAL;
    static const QString MESSAGE;
    static const QString RETRY_AFTER;

    RateLimit() {}
    RateLimit(const QByteArray &json) : JsonSerializable(json) {}
    RateLimit(const QJsonObject &json) : JsonSerializable(json) {}
    RateLimit(const QString &json) : JsonSerializable(json) {}

    QJsonValue getGlobal() const;
    QJsonValue getMessage() const;
    QJsonValue getRetryAfter() const;
    void setGlobal(const QJsonValue &global);
    void setMessage(const QJsonValue &message);
    void setRetryAfter(const QJsonValue &retryAfer);

    Q_PROPERTY(QJsonValue global READ getGlobal WRITE getGlobal)
    Q_PROPERTY(QJsonValue message READ getMessage WRITE getMessage)
    Q_PROPERTY(QJsonValue retry_After READ getRetryAfter WRITE getRetryAfter)
};

#endif // RATELIMIT_H
