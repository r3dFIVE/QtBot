#include <QDebug>
#include <QFile>
#include <QMetaEnum>
#include <QDir>

#include "settingsservice.h"
#include "globals.h"

SettingsService::SettingsService(QString path) : _path(path)
{
    parseSettingsFile();
    validateSettings();
}

void
SettingsService::parseSettingsFile() {
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
SettingsService::isComment(QString line) {
    return line.at(0) == "#" || line.at(0) == ";";
}

void
SettingsService::validateSettings() {
    validateConnectionSettings();
    validateDatabaseSettings();
    validateLoggingSettings();
}

void
SettingsService::validateConnectionSettings() {
    //    if (_settings->value(Settings::Connection::BOT_TOKEN).toString().isEmpty()) {

    //    }

        if (_settings[Settings::Connection::CONNECTION_URL].toString().isEmpty()) {
            _settings[Settings::Connection::CONNECTION_URL] = "wss://gateway.discord.gg";
        }
}

void
SettingsService::validateDatabaseSettings() {
    if (_settings[Settings::Database::DATABASE_TYPE].toString().isEmpty()) {
        _settings[Settings::Database::DATABASE_TYPE] = Settings::Database::DatabaseTypes::SQLITE;
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<Settings::Database::DatabaseTypes>();
    QString databaseType = _settings[Settings::Database::DATABASE_TYPE].toString();
    int typeValue = metaEnum.keyToValue(databaseType.toUpper().toStdString().c_str());
    if (typeValue < 0) {
        invalidEnumValue(Settings::Database::DATABASE_TYPE, databaseType, metaEnum);
    }

    if (typeValue != Settings::Database::DatabaseTypes::SQLITE) {
        if (_settings[Settings::Database::DATABASE_HOST].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_HOST);
        }

        if (_settings[Settings::Database::DATABASE_PORT].toInt() == 0) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_PORT);
        }

        if (_settings[Settings::Database::DATABASE_USER].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_USER);
        }

        if (_settings[Settings::Database::DATABASE_PASSWORD].toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_PASSWORD);
        }
    }
}

void
SettingsService::validateLoggingSettings() {
    QString consoleLogLevel = _settings[Settings::Logging::CONSOLE_LOG_LEVEL].toString();
    if (consoleLogLevel.isEmpty()) {
        _settings[Settings::Logging::CONSOLE_LOG_LEVEL] = Settings::Logging::Levels::INFO;
    } else {
        validateLogLevel(Settings::Logging::CONSOLE_LOG_LEVEL, consoleLogLevel);
    }


    QString fileLogLevel = _settings[Settings::Logging::FILE_LOG_LEVEL].toString();
    if (fileLogLevel.isEmpty()) {
        _settings[Settings::Logging::FILE_LOG_LEVEL] = Settings::Logging::Levels::INFO;
    } else {
        validateLogLevel(Settings::Logging::FILE_LOG_LEVEL, fileLogLevel);
    }

    if (_settings[Settings::Logging::LOG_FILE_SIZE].toInt() == 0) {
        _settings[Settings::Logging::LOG_FILE_SIZE] = 1048576;
    }

    if (_settings[Settings::Logging::LOG_FILE_COUNT].toInt() == 0) {
        _settings[Settings::Logging::LOG_FILE_COUNT] = 10;
    }

    if (_settings[Settings::Logging::LOG_FILE_DIRECTORY].toString().isEmpty()) {
        QString path = QDir::currentPath().append("/logs");
        _settings[Settings::Logging::LOG_FILE_DIRECTORY] = path;
    }
}

void
SettingsService::validateLogLevel(QString property, QString logLevel) {
    QMetaEnum metaEnum = QMetaEnum::fromType<Settings::Logging::Levels>();
    if (metaEnum.keyToValue(logLevel.toUpper().toStdString().c_str()) < 0) {
        invalidEnumValue(property, logLevel, metaEnum);
    }
}

void
SettingsService::invalidEnumValue(QString property, QString value, QMetaEnum metaEnum) {
    qDebug().noquote() << QString("[%1]").arg(_path) << "\n";
    qDebug().noquote() << QString("Invalid %1: %2\n").arg(property, value);
    qDebug() << "Possible values:";
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        qDebug().noquote() << "\t" << metaEnum.key(i);
    }
    exit(1);
}

void
SettingsService::invalidDatabaseProperty(QString databaseType, QString propertyName) {
    QString fileName = QString("[%1]").arg(_path);
    qDebug().noquote() << fileName << "\n";
    qDebug().noquote() << "Database Type: " << databaseType << "\n";
    qDebug().noquote() << QString("ERROR: Property \"%1\" cannot be blank.\n").arg(propertyName);
    exit(1);
}

QVariant
SettingsService::value(QString key) {
    return _settings[key];
}

void
SettingsService::setValue(QString key, QVariant value) {
    _settings[key] = value;
}

QString
SettingsService::fileName() {
    return _path;
}
