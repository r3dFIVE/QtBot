#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

/*************************
 * Settings file related *
 *************************/

namespace Settings {
//
// Connection properties
//
namespace Connection{
const QString BOT_TOKEN = "bot_token";
const QString CONNECTION_URL = "connection_url";
const QString ZLIB_ENABLED = "zlib_enabled";
}

//
// Logging proerties
//
namespace Logging{
const QString CONSOLE_LOG_LEVEL = "console_log_level";
const QString FILE_LOG_LEVEL = "file_log_level";
const QString LOG_FILE_SIZE = "log_file_size";
const QString LOG_FILE_COUNT = "log_file_count";
const QString LOG_FILE_DIRECTORY = "log_file_directory";

namespace Levels {
const QString TRACE = "trace";          // Level 0
const QString DEBUG = "debug";          // Level 1
const QString INFO = "info";            // Level 2
const QString WARN = "warn";            // Level 3
const QString ERROR = "error";          // Level 4
const QString CRITICAL = "critical";    // Level 5
const QString OFF = "off";              // Level 6
}
}

//
// Database properties
//
namespace Database {
const QString DATABASE_HOST = "database_host";
const QString DATABASE_PORT = "database_port";
const QString DATABASE_USER = "database_user";
//TODO PASSWORD HASH?
const QString DATABASE_PASSWORD = "database_password";
const QString DATABASE_TYPE = "database_type";

namespace DatabaseTypes {
const QString SQLITE = "SQLITE";
const QString MSSQL_SERVER = "MSSQL_SERVER";
const QString ORACLE = "ORACLE";
const QString POSTGRES = "POSTGRES";
}
}
}

#endif // GLOBALS_H
