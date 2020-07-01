#ifndef MESSAGEACTIVITY_H
#define MESSAGEACTIVITY_H

#include "jsonserializable.h"

#include <QObject>

class MessageActivity : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    QJsonValue type;

    Q_PROPERTY(QJsonValue party_id READ getPartyId WRITE setPartyId)
    QJsonValue party_id;

    QJsonValue getType() const;
    void setType(const QJsonValue &value);
    QJsonValue getPartyId() const;
    void setPartyId(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    MessageActivity() {}
    ~MessageActivity() {}
};

Q_DECLARE_METATYPE(MessageActivity)

#endif // MESSAGEACTIVITY_H
