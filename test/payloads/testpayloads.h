/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TEST_PAYLOADS_H
#define TEST_PAYLOADS_H

#include <QString>
#include <QJsonValue>

#include "util/gatewayevent.h"

const static QString TEST_STRING1 = "gfreeman";
const static QString TEST_STRING2 = "cstrife";
const static int TEST_INT1 = 42;
const static int TEST_INT2 = 24;

const static QString PLD_HELLO = QString("{\"heartbeat_interval\":%1}")
        .arg(TEST_INT1);

const static QString PLD_ACTIVITY_ASSETS_FULL = QString("{\"large_image\":\"%1\",\"large_text\":\"%2\",\"small_image\":\"%3\",\"small_text\":\"%4\"}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2);
const static QString PLD_ACTIVITY_ASSETS_MINIMAL = "{}";

const static QString PLD_ACTIVITY_EMOJI_FULL = QString("{\"name\":\"%1\",\"id\":\"%2\",\"animated\":%3}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg("true");
const static QString PLD_ACTIVITY_EMOJI_MINIMAL = QString("{\"name\":\"%1\"}")
        .arg(TEST_STRING1);

const static QString PLD_ACTIVITY_PARTY_FULL = QString("{\"id\":\"%1\",\"size\":[%2,%3]}")
        .arg(TEST_STRING1).arg(TEST_INT1).arg(TEST_INT2);
const static QString PLD_ACTIVITY_PARTY_MINIMAL = "{}";

const static QString PLD_ACTIVITY_SECRETS_FULL = QString("{\"join\":\"%1\",\"spectate\":\"%2\",\"match\":\"%3\"}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1);
const static QString PLD_ACTIVITY_SECRETS_MINIMAL = "{}";

const static QString PLD_ACTIVITY_TIMESTAMPS_FULL = QString("{\"start\":%1,\"end\":%2}")
        .arg(TEST_INT1).arg(TEST_INT2);
const static QString PLD_ACTIVITY_TIMESTAMPS_MINIMAL = "{}";

const static QString PLD_CLIENT_STATUS = QString("{\"desktop\":\"%1\",\"mobile\":\"%2\",\"web\":\"%3\"}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1);

const static QString PLD_GATEWAYPAYLOAD_FULL = "{\"op\":%1,\"d\":%2,\"s\":42,\"t\":\"GATEWAY_EVENT_NAME\"}";
const static QString PLD_GATEWAYPAYLOAD_MINIMAL = QString("{\"op\":%1,\"d\":%2}")
        .arg(GatewayEvent::HELLO).arg(PLD_HELLO);

const static QString PLD_HEARTBEAT = QString("{\"d\":%1,\"op\":1}")
        .arg(TEST_INT1);

const static QString PLD_INVALID_SESSION = "{\"op\":9,\"d\":true}";

const static QString PLD_PROPERTIES = QString("{\"$os\":\"%1\",\"$browser\":\"QtBot\",\"$device\":\"QtBot\"}")
        .arg(QSysInfo::productType());

const static QString PLD_RESUME = QString("{\"token\":\"%1\",\"session_id\":\"%2\",\"seq\":%3}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_INT1);

const static QString PLD_ROLE = QString("{\"id\":\"%1\",\"name\":\"%2\",\"color\":%3,\"hoist\":true,\"position\":1,\"permissions\":%4,\"managed\":true,\"mentionable\":true}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_INT1).arg(TEST_INT2);

const static QString PLD_PERMISSION_OVERWRITE = QString("{\"id\":\"%1\",\"type\":\"%2\",\"allow\":%3,\"deny\":%4}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_INT1).arg(TEST_INT2);

static const QString PLD_USER_FULL = QString("{\"id\":\"%1\",\"username\":\"%2\",\"discriminator\":\"%3\",\"avatar\":\"%4\",\"bot\":true,\"system\":true,\"mfa_enabled\":true,\"locale\":\"%5\",\"verified\":true,\"email\":\"%6\",\"flags\":1,\"premium_type\":1,\"public_flags\":1}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2)
        .arg(TEST_STRING1).arg(TEST_STRING2);
const static QString PLD_USER_MINIMAL = QString("{\"id\":\"%1\",\"username\":\"%2\",\"discriminator\":\"%3\"}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1);

const static QString PLD_ACTIVITY_FULL = QString("{\"name\":\"%1\",\"type\":1,\"url\":\"%2\",\"created_at\":%3,\"timestamps\":%4,\"application_id\":\"%5\",\"details\":\"%6\",\"state\":\"%7\",\"emoji\":%8,\"party\":%9,\"assets\":%10,\"secrets\":%11,\"instance\":true,\"flags\":1}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_INT1).arg(PLD_ACTIVITY_TIMESTAMPS_FULL)
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(PLD_ACTIVITY_EMOJI_FULL)
        .arg(PLD_ACTIVITY_PARTY_FULL).arg(PLD_ACTIVITY_ASSETS_FULL).arg(PLD_ACTIVITY_SECRETS_FULL);
const static QString PLD_ACTIVITY_MINIMAL = QString("{\"name\":\"%1\",\"type\":1,\"created_at\":%2}")
        .arg(TEST_STRING1).arg(TEST_INT1);

const static QString PLD_EMOJI_FULL = QString("{\"id\":\"%1\",\"name\":\"%2\",\"roles\":[\"%3\",\"%4\"],\"user\":%5,\"require_colons\":true,\"managed\":true,\"animated\":true,\"available\":true}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2).arg(PLD_USER_MINIMAL);
const static QString PLD_EMOJI_MINIMAL = QString("{\"id\":\"%1\",\"name\":\"%2\"}")
        .arg(TEST_STRING1).arg(TEST_STRING2);

const static QString PLD_GUILD_MEMBER_FULL = QString("{\"user\":%1,\"nick\":\"%2\",\"roles\":[\"%3\",\"%4\"],\"joined_at\":\"%5\",\"deaf\":true,\"mute\":true, \"premium_since\":\"%6\"}")
        .arg(PLD_USER_MINIMAL).arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1);
const static QString PLD_GUILD_MEMBER_MINIMAL = QString("{\"nick\":\"%2\",\"roles\":[\"%3\",\"%4\"],\"joined_at\":\"%5\",\"deaf\":true,\"mute\":true}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1);

const static QString PLD_VOICE_STATE_FULL = QString("{\"channel_id\":\"%1\",\"user_id\":\"%2\",\"session_id\":\"%3\",\"deaf\":true,\"mute\":true,\"self_deaf\":true,\"self_mute\":true,\"suppress\":true,\"guild_id\":\"%4\",\"member\":%5,\"self_stream\":true}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2).arg(PLD_GUILD_MEMBER_MINIMAL);
const static QString PLD_VOICE_STATE_MINIMAL = QString("{\"channel_id\":\"%1\",\"user_id\":\"%2\",\"session_id\":\"%3\",\"deaf\":true,\"mute\":true,\"self_deaf\":true,\"self_mute\":true,\"suppress\":true}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1);

const static QString PLD_UPDATE_STATUS = QString("{\"since\":%1,\"game\":%2,\"status\":\"%3\",\"afk\":true}")
        .arg(TEST_INT1).arg(PLD_ACTIVITY_MINIMAL).arg(TEST_STRING1);

const static QString PLD_IDENTIFY_FULL = QString("{\"token\":\"%1\",\"properties\":%2,\"compress\":true,\"large_threshold\":%3,\"guild_subscriptions\":true,\"shard\":[%4,%5],\"presence\":%6,\"intents\":%7}")
        .arg(TEST_STRING1).arg(PLD_PROPERTIES).arg(TEST_INT1).arg(TEST_INT2).arg(TEST_INT1).arg(PLD_UPDATE_STATUS)
        .arg(TEST_INT2);
const static QString PLD_IDENTIFY_MINIMAL = QString("{\"token\":\"%1\",\"properties\":%2}")
        .arg(TEST_STRING1).arg(PLD_PROPERTIES);

const static QString PLD_CHANNEL_FULL = QString("{\"id\":\"%1\",\"type\":%2,\"guild_id\":\"%3\",\"position\":%4,\"permission_overwrites\":[%5],\"name\":\"%6\",\"topic\":\"%7\",\"nsfw\":true,\"last_message_id\":\"%8\",\"bitrate\":%9,\"user_limit\":%10,\"rate_limit_per_user\":%11,\"recipients\":[%12],\"icon\":\"%13\",\"owner_id\":\"%14\",\"application_id\":\"%15\",\"parent_id\":\"%16\",\"last_pin_timestamp\":\"%17\"}")
        .arg(TEST_STRING1).arg(TEST_INT1).arg(TEST_STRING2).arg(TEST_INT2).arg(PLD_PERMISSION_OVERWRITE).arg(TEST_STRING1).arg(TEST_STRING2)
        .arg(TEST_STRING1).arg(TEST_INT1).arg(TEST_INT2).arg(TEST_INT1).arg(PLD_USER_MINIMAL).arg(TEST_STRING2).arg(TEST_STRING1)
        .arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2);
const static QString PLD_CHANNEL_MINIMAL = QString("{\"id\":\"%1\",\"type\":%2}")
        .arg(TEST_STRING1).arg(TEST_INT1);

const static QString PLD_PRESENCE_UPDATE_FULL = QString("{\"user\":%1,\"roles\":[\"%2\",\"%3\"],\"game\":%4,\"guild_id\":\"%5\",\"status\":\"%6\",\"activities\":[%7],\"client_status\":%8,\"premium_since\":\"%9\",\"nick\":\"%10\"}")
        .arg(PLD_USER_MINIMAL).arg(TEST_STRING1).arg(TEST_STRING2).arg(PLD_ACTIVITY_MINIMAL)
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(PLD_ACTIVITY_MINIMAL).arg(PLD_CLIENT_STATUS)
        .arg(TEST_STRING1).arg(TEST_STRING2);
const static QString PLD_PRESENCE_UPDATE_MINIMAL = QString("{\"user\":%1,\"roles\":[\"%2\",\"%3\"],\"game\":null,\"guild_id\":\"%5\",\"status\":\"%6\",\"activities\":[%7],\"client_status\":%8}")
        .arg(PLD_USER_MINIMAL).arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1)
        .arg(TEST_STRING2).arg(PLD_ACTIVITY_MINIMAL).arg(PLD_CLIENT_STATUS);

#endif // TEST_PAYLOADS_H
