#ifndef MESSAGEACTIVITY_H
#define MESSAGEACTIVITY_H

#include "jsonserializable.h"


class MessageActivity : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString PARTY_ID;
    static const QString TYPE;

    MessageActivity() {}
    MessageActivity(const QByteArray &json) : JsonSerializable(json) {}
    MessageActivity(const QJsonObject &json) : JsonSerializable(json) {}
    MessageActivity(const QString &json) : JsonSerializable(json) {}

    QJsonValue getPartyId() const;
    QJsonValue getType() const;
    void setPartyId(const QJsonValue &partyId);
    void setType(const QJsonValue &type);

    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue party_id READ getPartyId WRITE setPartyId)
};

Q_DECLARE_METATYPE(MessageActivity)

#endif // MESSAGEACTIVITY_H
