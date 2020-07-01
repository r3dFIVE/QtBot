#ifndef CHANNELMENTION_H
#define CHANNELMENTION_H

#include "jsonserializable.h"

#include <QObject>

class ChannelMention : public JsonSerializable
{
    Q_OBJECT

public:  
    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    QJsonValue id;

    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setId)
    QJsonValue guild_id;

    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    QJsonValue type;

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    QJsonValue name;

    QJsonValue getId();
    void setId(QJsonValue id);
    QJsonValue getGuildId();
    void setGuildId(QJsonValue guild_id);
    QJsonValue getType();
    void setType(QJsonValue type);
    QJsonValue getName();
    void setName(QJsonValue name);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    ChannelMention() {}
    ~ChannelMention() {}
};

Q_DECLARE_METATYPE(ChannelMention)

#endif // CHANNELMENTION_H
