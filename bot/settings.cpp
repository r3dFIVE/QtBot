#include <QDebug>
#include <QFile>
#include <QMetaEnum>
#include <QDir>

#include <logging/logcontext.h>

#include "settings.h"
#include "globals.h"

Settings::Settings(QString path) : _path(path)
{
    parseSettingsFile();
    validateSettings();
}

void
Settings::parseSettingsFile() {
    QFile settingsFile(_path);
    settingsFile.open(QIODevice::ReadOnly);

    if (!settingsFile.isOpen()) {
        qDebug().noquote() << QString("Error initializing opening %1. . . exiting.\n").arg(_path);
        exit(1);
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
    validateConnectionSettings();
    validateDatabaseSettings();
    validateLoggingSettings();
}

void
Settings::validateConnectionSettings() {
    //    if (_settings->value(Settings::Connection::BOT_TOKEN).toString().isEmpty()) {

    //    }

        if (_settings[SettingsParam::Connection::CONNECTION_URL].toString().isEmpty()) {
            _settings[SettingsParam::Connection::CONNECTION_URL] = "wss://gateway.discord.gg";
        }
}

void
Settings::validateDatabaseSettings() {
    if (_settings[SettingsParam::Database::DATABASE_TYPE].toString().isEmpty()) {
        _settings[SettingsParam::Database::DATABASE_TYPE] = SettingsParam::Database::DatabaseTypes::SQLITE;
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<SettingsParam::Database::DatabaseTypes>();
    QString databaseType = _settings[SettingsParam::Database::DATABASE_TYPE].toString();
    int typeValue = metaEnum.keyToValue(databaseType.toUpper().toStdString().c_str());
    if (typeValue < 0) {
        invalidEnumValue(SettingsParam::Database::DATABASE_TYPE, databaseType, metaEnum);
    }

    if (typeValue != SettingsParam::Database::DatabaseTypes::SQLITE) {
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
        _settings[SettingsParam::Logging::CONSOLE_LOG_LEVEL] = LogContext::LogLevel::INFO;
    } else {
        validateLogLevel(SettingsParam::Logging::CONSOLE_LOG_LEVEL, consoleLogLevel);
    }


    QString fileLogLevel = _settings[SettingsParam::Logging::FILE_LOG_LEVEL].toString();
    if (fileLogLevel.isEmpty()) {
        _settings[SettingsParam::Logging::FILE_LOG_LEVEL] = SettingsParam::Logging::FILE_LOG_LEVEL;
    } else {
        validateLogLevel(SettingsParam::Logging::FILE_LOG_LEVEL, fileLogLevel);
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
    if (metaEnum.keyToValue(logLevel.toUpper().toStdString().c_str()) < 0) {
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
    exit(1);
}

void
Settings::invalidDatabaseProperty(QString databaseType, QString propertyName) {
    QString fileName = QString("[%1]").arg(_path);
    qDebug().noquote() << fileName << "\n";
    qDebug().noquote() << "Database Type: " << databaseType << "\n";
    qDebug().noquote() << QString("ERROR: Property \"%1\" cannot be blank.\n").arg(propertyName);
    exit(1);
}

QVariant
Settings::value(QString key) {
    return _settings[key];
}
