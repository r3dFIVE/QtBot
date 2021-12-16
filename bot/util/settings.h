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

#ifndef SETTINGSSERVICE_H
#define SETTINGSSERVICE_H

#include <QMap>
#include <QObject>

class Settings
{
public:
    static void load(const QString &path);
    static QVariant value(const QString &key);

    static QString connectionUrl();
    static int maxRetries();
    static int apiVersion();
    static QString botToken();
    static QString ownerId();
    static QString adminRoleName();
    static QString restrictionState();
    static int consoleLogLevel();
    static QString databaseHost();
    static int databasePort();
    static QString databaseUser();
    static QString databasePassword();
    static QString databaseType();
    static QString databaseName();
    static QString gatewayIntents();
    static int maxPoolSize();
    static int fileLogLevel();
    static int logFileSize();
    static int logRolloverCount();
    static QString logFileDirectory();
    static QString logFileName();
    static QString scriptDirectory();
    static bool saveAttachments();

private:

    static const QString CONNECTION_URL;
    static const QString MAX_RETRIES;
    static const QString API_VERSION;
    static const QString BOT_TOKEN;
    static const QString OWNER_ID;
    static const QString ADMIN_ROLE_NAME;
    static const QString RESTRICTION_STATE;
    static const QString CONSOLE_LOG_LEVEL;
    static const QString DATABASE_HOST;
    static const QString DATABASE_PORT;
    static const QString DATABASE_USER;
    static const QString DATABASE_PASSWORD;
    static const QString DATABASE_TYPE;
    static const QString DATABASE_NAME;
    static const QString SAVE_ATTACHMENTS;
    static const QString GATEWAY_INTENTS;
    static const QString MAX_POOL_SIZE;
    static const QString FILE_LOG_LEVEL;
    static const QString LOG_FILE_SIZE;
    static const QString LOG_ROLLOVER_COUNT;
    static const QString LOG_FILE_DIRECTORY;
    static const QString LOG_FILE_NAME;
    static const QString SCRIPT_DIRECTORY;

    static QMap<QString, QVariant> _settings;

    static void validateSettings();
    static void validateBotSettings();
    static void validateDatabaseSettings();
    static void validateGatewaySettings();
    static void validateLoggingSettings();
    static void validateLogLevel(QString property, QString logLevel);
    static void invalidDatabaseProperty [[ noreturn ]] (QString databaseType, QString propertyName);
    static void invalidEnumValue [[ noreturn ]] (QString property, QString value, QMetaEnum metaEnum);
    static bool isComment(QString);
    static int valueFromEnumKey(QString key);
};


#endif // SETTINGSSERVICE_H
