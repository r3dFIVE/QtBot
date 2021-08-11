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
#include "settings.h"
#include "globals.h"
#include "enumutils.h"


Settings::Settings(QString path) : _path(path) {
    parseSettingsFile();    
    validateSettings();
}

void
Settings::parseSettingsFile() {
    QFile settingsFile(_path);

    settingsFile.open(QIODevice::ReadOnly);

    if (!settingsFile.isOpen()) {
        qDebug().noquote() << QString("Error initializing opening %1. . . exiting.\n").arg(_path);

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
}

bool
Settings::isComment(QString line) {
    return line.at(0) == "#" || line.at(0) == ";";
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
    if (_settings[SettingsParam::Bot::TOKEN].toString().isEmpty()) {
        qDebug() << "Bot Token must be set in your options file for successful conenctions";

        exit(EXIT_FAILURE);
    }

    if (_settings[SettingsParam::Bot::OWNER_ID].toString().isEmpty()) {
        qDebug() << "Bot Owner (discord user id) must be set in your options file.";

        exit(EXIT_FAILURE);
    }

    if (_settings[SettingsParam::Bot::ADMIN_ROLE_NAME].toString().isEmpty()) {
        qDebug() << "Guild level bot admin role name must be set in your options file.";

        exit(EXIT_FAILURE);
    }

    if (_settings[SettingsParam::Script::SCRIPT_DIRECTORY].toString().isEmpty()) {
        _settings[SettingsParam::Script::SCRIPT_DIRECTORY] = "./scripts/";
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<CommandRestrictions::RestrictionState>();

    QString restrictionState = _settings[SettingsParam::Bot::RESTRICTION_STATE].toString();

    int typeValue = metaEnum.keyToValue(restrictionState.toUtf8());

    if (typeValue < 0) {
        invalidEnumValue(SettingsParam::Bot::RESTRICTION_STATE, restrictionState, metaEnum);
    }
}

void
Settings::validateGatewaySettings() {
    if (_settings[SettingsParam::Connection::CONNECTION_URL].toString().isEmpty()) {
        _settings[SettingsParam::Connection::CONNECTION_URL] = "wss://gateway.discord.gg";
    }

    int max_retries = _settings[SettingsParam::Connection::MAX_RETRIES].toInt();

    if (max_retries <= 0) {
        _settings[SettingsParam::Connection::MAX_RETRIES] = 10;
    }

    if (_settings[SettingsParam::Gateway::GATEWAY_INTENTS].toString().isEmpty()) {
        _settings[SettingsParam::Gateway::GATEWAY_INTENTS] = "GUILD_MESSAGES";
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<Gateway::Intents>();

    QString intents = _settings[SettingsParam::Gateway::GATEWAY_INTENTS].toString();

    for (QString intentToken : intents.split(",")) {
        int typeValue = metaEnum.keyToValue(intentToken.toStdString().c_str());

        if (typeValue < 0) {
            invalidEnumValue(SettingsParam::Gateway::GATEWAY_INTENTS, intentToken, metaEnum);
        }
    }
}

void
Settings::validateDatabaseSettings() {
    if (_settings[SettingsParam::Database::DATABASE_TYPE].toString().isEmpty()) {
        _settings[SettingsParam::Database::DATABASE_TYPE] = SettingsParam::Database::DatabaseType::QSQLITE;
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<SettingsParam::Database::DatabaseType>();

    QString databaseType = _settings[SettingsParam::Database::DATABASE_TYPE].toString();

    int typeValue = metaEnum.keyToValue(databaseType.toStdString().c_str());

    if (typeValue < 0) {
        invalidEnumValue(SettingsParam::Database::DATABASE_TYPE, databaseType, metaEnum);
    }

    if (_settings[SettingsParam::Database::DATABASE_NAME].toString().isEmpty()) {
        invalidDatabaseProperty(databaseType, SettingsParam::Database::DATABASE_NAME);
    }

    if (typeValue != SettingsParam::Database::DatabaseType::QSQLITE
            && typeValue != SettingsParam::Database::DatabaseType::QMONGODB) {
        if (_settings[SettingsParam::Database::DATABASE_HOST].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, SettingsParam::Database::DATABASE_HOST);
        }

        if (_settings[SettingsParam::Database::DATABASE_PORT].toInt() == 0) {
            invalidDatabaseProperty(databaseType, SettingsParam::Database::DATABASE_PORT);
        }

        if (_settings[SettingsParam::Database::DATABASE_USER].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, SettingsParam::Database::DATABASE_USER);
        }

        if (_settings[SettingsParam::Database::DATABASE_PASSWORD].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, SettingsParam::Database::DATABASE_PASSWORD);
        }
    }
}

void
Settings::validateLoggingSettings() {
    QString consoleLogLevel = _settings[SettingsParam::Logging::CONSOLE_LOG_LEVEL].toString();
    if (consoleLogLevel.isEmpty()) {
        _settings[SettingsParam::Logging::CONSOLE_LOG_LEVEL] = LogContext::DEBUG;

    } else {
        validateLogLevel(SettingsParam::Logging::CONSOLE_LOG_LEVEL, consoleLogLevel);

        _settings[SettingsParam::Logging::CONSOLE_LOG_LEVEL] = EnumUtils::keyToValue<LogContext::LogLevel>(consoleLogLevel);
    }


    QString fileLogLevel = _settings[SettingsParam::Logging::FILE_LOG_LEVEL].toString();
    if (fileLogLevel.isEmpty()) {
        _settings[SettingsParam::Logging::FILE_LOG_LEVEL] = LogContext::DEBUG;

    } else {
        validateLogLevel(SettingsParam::Logging::FILE_LOG_LEVEL, fileLogLevel);

        _settings[SettingsParam::Logging::FILE_LOG_LEVEL] = EnumUtils::keyToValue<LogContext::LogLevel>(consoleLogLevel);
    }

    if (_settings[SettingsParam::Logging::LOG_FILE_SIZE].toInt() == 0) {
        _settings[SettingsParam::Logging::LOG_FILE_SIZE] = 1048576;
    }

    if (_settings[SettingsParam::Logging::LOG_ROLLOVER_COUNT].toInt() == 0) {
        _settings[SettingsParam::Logging::LOG_ROLLOVER_COUNT] = 10;
    }

    if (_settings[SettingsParam::Logging::LOG_FILE_DIRECTORY].toString().isEmpty()) {
        QString path = QDir::currentPath().append("/logs");

        _settings[SettingsParam::Logging::LOG_FILE_DIRECTORY] = path;
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
    qDebug().noquote() << QString("[%1]").arg(_path) << "\n";

    qDebug().noquote() << QString("Invalid %1: %2\n").arg(property, value);

    qDebug() << "Possible values:";

    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        qDebug().noquote() << "\t" << metaEnum.key(i);
    }

    exit(EXIT_FAILURE);
}

void
Settings::invalidDatabaseProperty(QString databaseType, QString propertyName) {
    QString fileName = QString("[%1]").arg(_path);

    qDebug().noquote() << fileName << "\n";

    qDebug().noquote() << "Database Type: " << databaseType << "\n";

    qDebug().noquote() << QString("ERROR: Property \"%1\" cannot be blank.\n").arg(propertyName);

    exit(EXIT_FAILURE);
}

QVariant
Settings::value(QString key) {
    return _settings[key];
}
