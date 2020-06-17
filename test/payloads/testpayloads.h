#ifndef TEST_PAYLOADS_H
#define TEST_PAYLOADS_H

#include <QString>
#include <QJsonValue>
#include "globals.h"

static QString TEST_STRING1 = "gfreeman";
static QString TEST_STRING2 = "cstrife";
static int TEST_INT1 = 42;
static int TEST_INT2 = 24;

static QString PLD_HELLO = QString("{\"heartbeat_interval\":%1}")
        .arg(TEST_INT1);

static QString PLD_ASSETS_FULL = QString("{\"large_image\":\"%1\",\"large_text\":\"%2\",\"small_image\":\"%3\",\"small_text\":\"%4\"}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(TEST_STRING2);
static QString PLD_ASSETS_MINIMAL = "{}";
static QString PLD_EMOJI_FULL = QString("{\"name\":\"%1\",\"id\":\"%2\",\"animated\":%3}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg("true");
static QString PLD_EMOJI_MINIMAL = QString("{\"name\":\"%1\"}")
        .arg(TEST_STRING1);
static QString PLD_GATEWAYPAYLOAD_FULL = "{\"op\":%1,\"d\":%2,\"s\":42,\"t\":\"GATEWAY_EVENT_NAME\"}";
static QString PLD_GATEWAYPAYLOAD_MINIMAL = QString("{\"op\":%1,\"d\":%2}")
        .arg(GatewayOpcodes::HELLO).arg(PLD_HELLO);
static QString PLD_HEARTBEAT = QString("{\"d\":%1,\"op\":1}")
        .arg(TEST_INT1);
static QString PLD_PARTY_FULL = QString("{\"id\":\"%1\",\"size\":[%2,%3]}")
        .arg(TEST_STRING1).arg(TEST_INT1).arg(TEST_INT2);
static QString PLD_PARTY_MINIMAL = "{}";
static QString PLD_SECRETS_FULL = QString("{\"join\":\"%1\",\"spectate\":\"%2\",\"match\":\"%3\"}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1);
static QString PLD_SECRETS_MINIMAL = "{}";
static QString PLD_TIMESTAMPS_FULL = QString("{\"start\":%1,\"end\":%2}")
        .arg(TEST_INT1).arg(TEST_INT2);
static QString PLD_TIMESTAMPS_MINIMAL = "{}";

static QString PLD_ACTIVITY_FULL = QString("{\"name\":\"%1\",\"type\":1,\"url\":\"%2\",\"created_at\":%3,\"timestamps\":%4,\"application_id\":\"%5\",\"details\":\"%6\",\"state\":\"%7\",\"emoji\":%8,\"party\":%9,\"assets\":%10,\"secrets\":%11,\"instance\":true,\"flags\":1}")
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_INT1).arg(PLD_TIMESTAMPS_FULL)
        .arg(TEST_STRING1).arg(TEST_STRING2).arg(TEST_STRING1).arg(PLD_EMOJI_FULL)
        .arg(PLD_PARTY_FULL).arg(PLD_ASSETS_FULL).arg(PLD_SECRETS_FULL);
static QString PLD_ACTIVITY_MINIMAL = QString("{\"name\":\"%1\",\"type\":1,\"created_at\":%2}")
        .arg(TEST_STRING1).arg(TEST_INT1);

#endif // TEST_PAYLOADS_H
