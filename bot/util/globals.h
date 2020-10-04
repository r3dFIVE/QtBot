#ifndef GLOBALS_H
#define GLOBALS_H

#include <QObject>


static const int MS_FIVE_SECONDS = 5000;
static const int IMMEDIATE = 0;
static const QString DEFAULT_GUILD_ID = "0";

/*************************
 * Settings file related *
 *************************/

namespace SettingsParam {
//
// Bot Control Properties
//
namespace Bot {
static const QString TOKEN = "bot_token";
static const QString OWNER_ID = "owner_id";
static const QString ADMIN_ROLE_NAME = "admin_role_name";
static const QString RESTRICTION_SCHEME = "restriction_scheme";
}

//
// Connection properties
//
namespace Connection {
static const QString CONNECTION_URL = "connection_url";
static const QString MAX_RETRIES = "max_retries";
static const QString ZLIB_ENABLED = "zlib_enabled";
}

namespace Gateway {
static const QString GATEWAY_INTENTS = "gateway_intents";
}

namespace Script {
static const QString SCRIPT_DIRECTORY = "script_directory";
}

//
// Logging proerties
//
namespace Logging {
static const QString CONSOLE_LOG_LEVEL = "console_log_level";
static const QString FILE_LOG_LEVEL = "file_log_level";
static const QString LOG_FILE_SIZE = "log_file_size";
static const QString LOG_ROLLOVER_COUNT = "log_rollover_count";
static const QString LOG_FILE_DIRECTORY = "log_file_directory";
static const QString LOG_FILE_NAME = "log_file_name";
}

//
// Database properties
//
namespace Database {
Q_NAMESPACE

static const QString DATABASE_HOST = "database_host";
static const QString DATABASE_PORT = "database_port";
static const QString DATABASE_USER = "database_user";
//TODO PASSWORD HASH?
static const QString DATABASE_PASSWORD = "database_password";
static const QString DATABASE_TYPE = "database_type";
static const QString DATABASE_NAME = "database_name";

enum DatabaseType {
    QSQLITE = 0,
    QODBC,
    QMYSQL,
    QPSQL
};
Q_ENUM_NS(DatabaseType)
}
}

namespace GatewayEvent {
Q_NAMESPACE

enum Event {
    /* Invalid Event */
    INVALID = -1,

    /* Gateway Opcodes */
    DISPATCH = 0,
    HEARTBEAT = 1,
    IDENTIFY = 2,
    STATUS_UPDATE = 3,
    VOICE_STATUS_UPDATE = 4,
    RESUME = 6,
    RECONNECT = 7,
    REQUEST_GUILD_MEMBERS = 8,
    INVALID_SESSION = 9,
    HELLO = 10,
    HEARTBEAT_ACK = 11,

    /* Gateway Dispatches */
    READY,
    RESUMED,
    CHANNEL_CREATE,
    CHANNEL_UPDATE,
    CHANNEL_DELETE,
    CHANNEL_PINS_UPDATE,
    GUILD_CREATE,
    GUILD_UPDATE,
    GUILD_DELETE,
    GUILD_BAN_ADD,
    GUILD_BAN_REMOVE,
    GUILD_EMOJIS_UPDATE,
    GUILD_INTEGRATIONS_UPDATE,
    GUILD_MEMBER_ADD,
    GUILD_MEMBER_REMOVE,
    GUILD_MEMBER_UPDATE,
    GUILD_MEMBERS_CHUNK,
    GUILD_ROLE_CREATE,
    GUILD_ROLE_UPDATE,
    GUILD_ROLE_DELETE,
    INVITE_CREATE,
    INVITE_DELETE,
    MESSAGE_CREATE,
    MESSAGE_UPDATE,
    MESSAGE_DELETE,
    MESSAGE_DELETE_BULK,
    MESSAGE_REACTION_ADD,
    MESSAGE_REACTION_REMOVE,
    MESSAGE_REACTION_REMOVE_ALL,
    PRESENCE_UPDATE,
    TYPING_START,
    USER_UPDATE,
    VOICE_STATE_UPDATE,
    VOICE_SERVER_UPDATE,
    WEBHOOKS_UPDATE
};
Q_ENUM_NS(Event)
}

#endif // GLOBALS_H
