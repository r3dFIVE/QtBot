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

#include <QDebug>
#include <QFile>
#include <QMetaEnum>
#include <QDir>
#include <gateway.h>

#include "logging/logcontext.h"
#include "entity/guildentity.h"
#include "util/databasetype.h"
#include "settings.h"
#include "enumutils.h"


QMap<QString, QVariant> Settings::_settings = QMap<QString, QVariant>();
const QString Settings::CONNECTION_URL = QString("connection_url");
const QString Settings::MAX_RETRIES = QString("max_retries");
const QString Settings::API_VERSION = QString("api_version");
const QString Settings::BOT_TOKEN = QString("bot_token");
const QString Settings::OWNER_ID = QString("owner_id");
const QString Settings::ADMIN_ROLE_NAME = QString("admin_role_name");
const QString Settings::RESTRICTION_STATE = QString("restriction_state");
const QString Settings::CONSOLE_LOG_LEVEL = QString("console_log_level");
const QString Settings::FILE_LOG_LEVEL = QString("file_log_level");
const QString Settings::LOG_FILE_SIZE = QString("log_file_size");
const QString Settings::LOG_ROLLOVER_COUNT = QString("log_rollover_count");
const QString Settings::LOG_FILE_DIRECTORY = QString("log_file_directory");
const QString Settings::LOG_FILE_NAME = QString("log_file_name");
const QString Settings::DATABASE_HOST = QString("database_host");
const QString Settings::DATABASE_PORT = QString("database_port");
const QString Settings::DATABASE_USER = QString("database_user");
const QString Settings::DATABASE_PASSWORD = QString("database_password");
const QString Settings::DATABASE_TYPE = QString("database_type");
const QString Settings::DATABASE_NAME = QString("database_name");
const QString Settings::SAVE_ATTACHMENTS = QString("save_attachments");
const QString Settings::GATEWAY_INTENTS = QString("gateway_intents");
const QString Settings::MAX_POOL_SIZE = QString("max_pool_size");
const QString Settings::SCRIPT_DIRECTORY = QString("script_directory");


void
Settings::load(const QString &path) {
    QFile settingsFile(path);

    settingsFile.open(QIODevice::ReadOnly);

    if (!settingsFile.isOpen()) {
        qDebug().noquote() << QString("Error initializing opening %1. . . exiting.\n").arg(path);

        exit(EXIT_FAILURE);
    }

    QTextStream stream(&settingsFile);

    QString line = stream.readLine();

    while(!line.isNull()) {
        line = line.trimmed();

        if (!line.isEmpty() && !isComment(line)) {
            if (line.contains("=")) {
                QStringList settingsTokens = line.split("=");

                _settings[settingsTokens[0].trimmed()] = settingsTokens[1].trimmed();
            }
        }

        line = stream.readLine();
    }

    validateSettings();
}

bool
Settings::isComment(QString line) {
    return line.at(0) == '#' || line.at(0) == ';';
}

void
Settings::validateSettings() {
    validateBotSettings();
    validateGatewaySettings();
    validateDatabaseSettings();
    validateLoggingSettings();
}

void
Settings::validateBotSettings() {
    if (_settings[BOT_TOKEN].toString().isEmpty()) {
        qDebug() << "Bot Token must be set in your options file for successful conenctions";

        exit(EXIT_FAILURE);
    }

    if (_settings[OWNER_ID].toString().isEmpty()) {
        qDebug() << "Bot Owner (discord user id) must be set in your options file.";

        exit(EXIT_FAILURE);
    }

    if (_settings[ADMIN_ROLE_NAME].toString().isEmpty()) {
        qDebug() << "Guild level bot admin role name must be set in your options file.";

        exit(EXIT_FAILURE);
    }

    if (_settings[SCRIPT_DIRECTORY].toString().isEmpty()) {
        _settings[SCRIPT_DIRECTORY] = "./scripts/";
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<CommandRestrictions::RestrictionState>();

    QString restrictionState = _settings[RESTRICTION_STATE].toString();

    int typeValue = metaEnum.keyToValue(restrictionState.toUtf8());

    if (typeValue < 0) {
        invalidEnumValue(RESTRICTION_STATE, restrictionState, metaEnum);
    }
}

void
Settings::validateGatewaySettings() {
    if (_settings[CONNECTION_URL].toString().isEmpty()) {
        _settings[CONNECTION_URL] = "wss://gateway.discord.gg";
    }

    int max_retries = _settings[MAX_RETRIES].toInt();

    if (max_retries <= 0) {
        _settings[MAX_RETRIES] = 10;
    }

    if (_settings[GATEWAY_INTENTS].toString().isEmpty()) {
        _settings[GATEWAY_INTENTS] = "GUILD_MESSAGES";
    }

    if (_settings[API_VERSION].toString().isEmpty()) {
        _settings[API_VERSION] = 9;
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<Gateway::Intents>();

    QString intents = _settings[GATEWAY_INTENTS].toString();

    for (QString intentToken : intents.split(",")) {
        int typeValue = metaEnum.keyToValue(intentToken.toStdString().c_str());

        if (typeValue < 0) {
            invalidEnumValue(GATEWAY_INTENTS, intentToken, metaEnum);
        }
    }
}

void
Settings::validateDatabaseSettings() {
    if (_settings[DATABASE_TYPE].toString().isEmpty()) {
        _settings[DATABASE_TYPE] = DatabaseType::QMONGODB;
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<DatabaseType::Type>();

    QString databaseType =  _settings[DATABASE_TYPE].toString();

    int typeValue = metaEnum.keyToValue(databaseType.toStdString().c_str());

    if (typeValue < 0) {
        invalidEnumValue(DATABASE_TYPE, databaseType, metaEnum);
    }

    if (_settings[DATABASE_NAME].toString().isEmpty()) {
        invalidDatabaseProperty(databaseType, DATABASE_NAME);
    }

    if (typeValue == DatabaseType::QMONGODB) {
        if (_settings[DATABASE_HOST].toString().isEmpty()) {
            _settings[DATABASE_HOST] = "127.0.0.1";
        }

        if (_settings[DATABASE_PORT].toInt() == 0) {
            _settings[DATABASE_PORT] = 27017;
        }

    } else if (typeValue != DatabaseType::QSQLITE) {
        if (_settings[DATABASE_HOST].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, DATABASE_HOST);
        }

        if (_settings[DATABASE_PORT].toInt() == 0) {
            invalidDatabaseProperty(databaseType, DATABASE_PORT);
        }

        if (_settings[DATABASE_USER].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, DATABASE_USER);
        }

        if (_settings[DATABASE_PASSWORD].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, DATABASE_PASSWORD);
        }
    }

    if (_settings[MAX_POOL_SIZE].toString().isEmpty()) {

        _settings[MAX_POOL_SIZE] = 10;
    }

    int maxPoolSize = _settings[MAX_POOL_SIZE].toInt();

    if (maxPoolSize <= 0) {
        qDebug() << QString("max_pool_size (%1) must be greater 0").arg(maxPoolSize);

        exit(EXIT_FAILURE);
    }

    if (typeValue == DatabaseType::QMONGODB) {
        QString boolStr = _settings[SAVE_ATTACHMENTS].toString().toLower();

        if (boolStr != "false" && boolStr != "true") {
            qDebug() << QString("%1 must be either 'true' or 'false', was given: %2. Defaulting to 'false'")
                        .arg(SAVE_ATTACHMENTS, boolStr);

            boolStr = "false";
        }

        _settings[SAVE_ATTACHMENTS] = QVariant(boolStr).toBool();
    } else {
         _settings[SAVE_ATTACHMENTS] = false;
    }
}

void
Settings::validateLoggingSettings() {
    QString consoleLogLevel = _settings[CONSOLE_LOG_LEVEL].toString();
    if (consoleLogLevel.isEmpty()) {
        _settings[CONSOLE_LOG_LEVEL] = LogContext::DEBUG;

    } else {
        validateLogLevel(CONSOLE_LOG_LEVEL, consoleLogLevel);

        _settings[CONSOLE_LOG_LEVEL] = EnumUtils::keyToValue<LogContext::LogLevel>(consoleLogLevel);
    }


    QString fileLogLevel = _settings[FILE_LOG_LEVEL].toString();
    if (fileLogLevel.isEmpty()) {
        _settings[FILE_LOG_LEVEL] = LogContext::DEBUG;

    } else {
        validateLogLevel(FILE_LOG_LEVEL, fileLogLevel);

        _settings[FILE_LOG_LEVEL] = EnumUtils::keyToValue<LogContext::LogLevel>(consoleLogLevel);
    }

    if (_settings[LOG_FILE_SIZE].toInt() == 0) {
        _settings[LOG_FILE_SIZE] = 10485760;
    }

    if (_settings[LOG_ROLLOVER_COUNT].toInt() == 0) {
        _settings[LOG_ROLLOVER_COUNT] = 10;
    }

    if (_settings[LOG_FILE_DIRECTORY].toString().isEmpty()) {
        QString path = QDir::currentPath().append("/logs");

        _settings[LOG_FILE_DIRECTORY] = path;
    }
}

void
Settings::validateLogLevel(QString property, QString logLevel) {
    QMetaEnum metaEnum = QMetaEnum::fromType<LogContext::LogLevel>();

    if (EnumUtils::keyToValue<LogContext::LogLevel>(logLevel) < 0) {
        invalidEnumValue(property, logLevel, metaEnum);
    }
}

void
Settings::invalidEnumValue(QString property, QString value, QMetaEnum metaEnum) {
    qDebug().noquote() << QString("Invalid %1: %2\n").arg(property, value);

    qDebug().noquote() << "Possible values:";

    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        qDebug().noquote() << "\t" << metaEnum.key(i);
    }

    exit(EXIT_FAILURE);
}

void
Settings::invalidDatabaseProperty(QString databaseType, QString propertyName) {
    qDebug().noquote() << "Database Type: " << databaseType << "\n";

    qDebug().noquote() << QString("ERROR: Property \"%1\" cannot be blank.\n").arg(propertyName);

    exit(EXIT_FAILURE);
}

QString
Settings::connectionUrl() {
    return _settings[CONNECTION_URL].toString();
}

int
Settings::maxRetries() {
    return _settings[MAX_RETRIES].toInt();
}

int
Settings::apiVersion() {
    return _settings[API_VERSION].toInt();
}

QString
Settings::botToken() {
    return _settings[BOT_TOKEN].toString();
}

QString
Settings::ownerId() {
    return _settings[OWNER_ID].toString();
}

QString
Settings::adminRoleName() {
    return _settings[ADMIN_ROLE_NAME].toString();
}

QString
Settings::restrictionState() {
    return _settings[RESTRICTION_STATE].toString();
}

int
Settings::consoleLogLevel() {
    return _settings[CONSOLE_LOG_LEVEL].toInt();
}

QString
Settings::databaseHost() {
    return _settings[DATABASE_HOST].toString();
}

int
Settings::databasePort() {
    return _settings[DATABASE_PORT].toInt();
}

QString
Settings::databaseUser() {
    return _settings[DATABASE_USER].toString();
}

QString
Settings::databasePassword() {
    return _settings[DATABASE_PASSWORD].toString();
}

QString
Settings::databaseType() {
    return _settings[DATABASE_TYPE].toString();
}

QString
Settings::databaseName() {
    return _settings[DATABASE_NAME].toString();
}

QString
Settings::gatewayIntents() {
    return _settings[GATEWAY_INTENTS].toString();
}

int
Settings::maxPoolSize() {
    return _settings[MAX_POOL_SIZE].toInt();
}

int
Settings::fileLogLevel() {
    return _settings[FILE_LOG_LEVEL].toInt();
}

int
Settings::logFileSize() {
    return _settings[LOG_FILE_SIZE].toInt();
}

int
Settings::logRolloverCount() {
    return _settings[LOG_ROLLOVER_COUNT].toInt();
}

QString
Settings::logFileDirectory() {
    return _settings[LOG_FILE_DIRECTORY].toString();
}

QString
Settings::logFileName() {
    return _settings[LOG_FILE_NAME].toString();
}

QString
Settings::scriptDirectory() {
    return _settings[SCRIPT_DIRECTORY].toString();
}

bool
Settings::saveAttachments() {
    return _settings[SAVE_ATTACHMENTS].toBool();
}
