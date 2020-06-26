#ifndef GLOBALS_H
#define GLOBALS_H

#include <QObject>


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
    MSSQL_SERVER,
    ORACLE,
    POSTGRES
};
Q_ENUM_NS(DatabaseTypes)
}
}

enum GatewayOpcodes {
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
    HEARTBEAT_ACK = 11
};

namespace GatewayEvents {
    static const QString READY = "READY";
};

#endif // GLOBALS_H
