#ifndef GUILDROLEDELETE_H
#define GUILDROLEDELETE_H

#include "jsonserializable.h"

class GuildRoleDelete : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString GUILD_ID;
    static const QString ROLE_ID;

    GuildRoleDelete() {}
    GuildRoleDelete(const QByteArray &json) : JsonSerializable(json) {}
    GuildRoleDelete(const QJsonObject &json) : JsonSerializable(json) {}
    GuildRoleDelete(const QString &json) : JsonSerializable(json) {}

    QJsonValue getGuildId() const;
    QJsonValue getRoleId() const;
    void setGuildId(const QJsonValue &guildId);
    void setRoleId(const QJsonValue &roleId);
};

Q_DECLARE_METATYPE(GuildRoleDelete)

#endif // GUILDROLEDELETE_H
