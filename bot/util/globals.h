#ifndef GLOBALS_H
#define GLOBALS_H

#include <QObject>

#include "payloads/gatewaypayload.h"


/*************************
 * Settings file related *
 *************************/

namespace SettingsParam {
//
// Connection properties
//
namespace Connection {
static const QString BOT_TOKEN = "bot_token";
static const QString CONNECTION_URL = "connection_url";
static const QString MAX_RETRIES = "max_retries";
static const QString ZLIB_ENABLED = "zlib_enabled";
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

enum DatabaseTypes {
    SQLITE = 0,
    MSSQLSERVER,
    MYSQL,
    POSTGRES
};
Q_ENUM_NS(DatabaseTypes)
}
}

namespace GatewayEvents {
Q_NAMESPACE

enum Events {
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
Q_ENUM_NS(Events)
}

#endif // GLOBALS_H
