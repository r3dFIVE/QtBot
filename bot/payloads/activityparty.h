#ifndef PARTY_H
#define PARTY_H

#include "jsonserializable.h"


class ActivityParty : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString SIZE;

    ActivityParty() {}
    ActivityParty(const QByteArray &json) : JsonSerializable(json) {}
    ActivityParty(const QJsonObject &json) : JsonSerializable(json) {}
    ActivityParty(const QString &json) : JsonSerializable(json) {}

    QJsonArray getSize() const;
    QJsonValue getId() const;
    void setId(const QJsonValue &id);
    void setSize(const QJsonArray &size);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonArray size READ getSize WRITE setSize)
};

Q_DECLARE_METATYPE(ActivityParty)

#endif // PARTY_H
