#include "guildroledelete.h"


const QString GuildRoleDelete::GUILD_ID = "guild_id";
const QString GuildRoleDelete::ROLE_ID = "role_id";

QJsonValue
GuildRoleDelete::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
GuildRoleDelete::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}


QJsonValue
GuildRoleDelete::getRoleId() const {
    return _jsonObject[ROLE_ID];
}

void
GuildRoleDelete::setRoleId(const QJsonValue &roleId) {
    _jsonObject[ROLE_ID] = roleId;
}
