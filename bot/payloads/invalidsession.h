#ifndef INVALIDSESSION_H
#define INVALIDSESSION_H

#include "jsonserializable.h"


class InvalidSession : public JsonSerializable
{
    Q_OBJECT
public:
    static const QString D;
    static const QString OP;

    InvalidSession() {}
    InvalidSession(const QByteArray &json) : JsonSerializable(json) {}
    InvalidSession(const QJsonObject &json) : JsonSerializable(json) {}
    InvalidSession(const QString &json) : JsonSerializable(json) {}

    QJsonValue getD() const;
    QJsonValue getOP() const;
    void setD(const QJsonValue &d);
    void setOP(const QJsonValue &op);

    Q_PROPERTY(QJsonValue d READ getD WRITE setD)
    Q_PROPERTY(QJsonValue op READ getOP WRITE setOP)
};

#endif // INVALIDSESSION_H
