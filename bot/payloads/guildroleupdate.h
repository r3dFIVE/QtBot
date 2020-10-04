#ifndef GUILDROLEUPDATE_H
#define GUILDROLEUPDATE_H

#include <QObject>

#include "jsonserializable.h"


class GuildRoleUpdate : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString GUILD_ID;
    static const QString ROLE;

    GuildRoleUpdate() {}
    GuildRoleUpdate(const QByteArray &json) : JsonSerializable(json) {}
    GuildRoleUpdate(const QJsonObject &json) : JsonSerializable(json) {}
    GuildRoleUpdate(const QString &json) : JsonSerializable(json) {}

    QJsonValue getGuildId() const;
    QJsonObject getRole() const;
    void setGuildId(const QJsonValue &guildId);
    void setRole(const QJsonObject &object);

    Q_PROPERTY(QJsonObject role READ getRole WRITE setRole)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)

};

Q_DECLARE_METATYPE(GuildRoleUpdate)

#endif // GUILDROLEUPDATE_H
