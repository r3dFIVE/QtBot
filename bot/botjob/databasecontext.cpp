#include "databasecontext.h"

#include "util/globals.h"
#include "util/enumutils.h"

DatabaseContext::DatabaseContext(QSharedPointer<Settings> settings) {
    hostName = settings->value(SettingsParam::Database::DATABASE_HOST).toString();

    port = settings->value(SettingsParam::Database::DATABASE_PORT).toInt();

    userName = settings->value(SettingsParam::Database::DATABASE_USER).toString();

    password = settings->value(SettingsParam::Database::DATABASE_PASSWORD).toString();

    driverName = settings->value(SettingsParam::Database::DATABASE_TYPE).toString();

    type = EnumUtils::keyToValue<SettingsParam::Database::DatabaseType>(driverName);

    databaseName = settings->value(SettingsParam::Database::DATABASE_NAME).toString();
}

DatabaseContext::DatabaseContext(const DatabaseContext &other) {
    hostName = other.hostName;

    port = other.port;

    userName = other.userName;

    password = other.password;

    driverName = other.driverName;

    type = other.type;

    guildId = other.guildId;

    scriptName = other.scriptName;
}


void
DatabaseContext::setConnectionName(const QString &scriptName, const QString &guildId) {
    _connectionName = QString("%1|%2|%3")
            .arg(scriptName)
            .arg(guildId)
            .arg(type);
}

QString
DatabaseContext::getConnectionName() const {
    return _connectionName;
}
