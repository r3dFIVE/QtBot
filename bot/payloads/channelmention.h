#ifndef CHANNELMENTION_H
#define CHANNELMENTION_H

#include "jsonserializable.h"

#include <QObject>

class ChannelMention : public JsonSerializable
{
    Q_OBJECT

public:      
    static const QString ID;
    static const QString GUILD_ID;
    static const QString TYPE;
    static const QString NAME;

    ChannelMention() {}
    ChannelMention(const QByteArray &json) : JsonSerializable(json) {}
    ChannelMention(const QJsonObject &json) : JsonSerializable(json) {}
    ChannelMention(const QString &json) : JsonSerializable(json) {}

    QJsonValue getGuildId() const;
    QJsonValue getId() const;
    QJsonValue getName() const;
    QJsonValue getType() const;
    void setGuildId(const QJsonValue &guild_id);
    void setId(const QJsonValue &id);
    void setName(const QJsonValue &name);
    void setType(const QJsonValue &type);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setId)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
};

Q_DECLARE_METATYPE(ChannelMention)

#endif // CHANNELMENTION_H
