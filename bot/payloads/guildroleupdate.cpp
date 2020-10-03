#include "guildroleupdate.h"


const QString GuildRoleUpdate::GUILD_ID = "guild_id";
const QString GuildRoleUpdate::ROLE = "role";

QJsonValue
GuildRoleUpdate::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
GuildRoleUpdate::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonObject
GuildRoleUpdate::getRole() const {
    return _jsonObject[ROLE].toObject();
}

void
GuildRoleUpdate::setRole(const QJsonObject &role) {
    _jsonObject[ROLE] = role;
}
