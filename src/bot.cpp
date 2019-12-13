#include "bot.h"
#include "eventservice.h"
#include "globals.h"

#include <QDir>
#include <QMetaEnum>


Bot::Bot(QSharedPointer<QSettings> settings) : _settings(settings)
{
    qRegisterMetaType<QSharedPointer<JsonSerializeable>>();

    validateSettings();
    initializeLogging();

    _logger->info("QtBot is now starting. . .");

//    qDebug() << QSysInfo::kernelType();
//    qDebug() << _settings->isWritable();
//    qDebug() << _settings->value("test_val").toBool();
//    qDebug() << _settings->value("bot_token").toString();
//    qDebug() << _settings->value("invalid_token").isNull();
}

void
Bot::validateSettings() {
    if (!_settings) {
        qDebug() << "Error initializing settings file. . . exiting.";
        exit(1);
    }

    validateConnectionSettings();
    validateDatabaseSettings();
    validateLoggingSettings();
}

void
Bot::validateConnectionSettings() {
    //    if (_settings->value(Settings::Connection::BOT_TOKEN).toString().isEmpty()) {

    //    }

        if (_settings->value(Settings::Connection::CONNECTION_URL).toString().isEmpty()) {
            _settings->setValue(Settings::Connection::CONNECTION_URL, "wss://gateway.discord.gg");
        }
}

void
Bot::validateDatabaseSettings() {
    if (_settings->value(Settings::Database::DATABASE_TYPE).toString().isEmpty()) {
        _settings->setValue(Settings::Database::DATABASE_TYPE, Settings::Database::DatabaseTypes::SQLITE);
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<Settings::Database::DatabaseTypes>();
    QString databaseType = _settings->value(Settings::Database::DATABASE_TYPE).toString();
    int typeValue = metaEnum.keyToValue(databaseType.toUpper().toStdString().c_str());
    if (typeValue < 0) {
        invalidEnumValue(Settings::Database::DATABASE_TYPE, databaseType, metaEnum);
    }

    if (typeValue != Settings::Database::DatabaseTypes::SQLITE) {
        if (_settings->value(Settings::Database::DATABASE_HOST).toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_HOST);
        }

        if (_settings->value(Settings::Database::DATABASE_PORT).toInt() == 0) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_PORT);
        }

        if (_settings->value(Settings::Database::DATABASE_USER).toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_USER);
        }

        if (_settings->value(Settings::Database::DATABASE_PASSWORD).toString().isEmpty()) {
            invalidDatabaseProperty(databaseType, Settings::Database::DATABASE_PASSWORD);
        }
    }
}

void
Bot::validateLoggingSettings() {
    QString consoleLogLevel = _settings->value(Settings::Logging::CONSOLE_LOG_LEVEL).toString();
    if (consoleLogLevel.isEmpty()) {
        _settings->value(Settings::Logging::CONSOLE_LOG_LEVEL) = Settings::Logging::Levels::INFO;
    } else {
        validateLogLevel(Settings::Logging::CONSOLE_LOG_LEVEL, consoleLogLevel);
    }

    QString fileLogLevel = _settings->value(Settings::Logging::FILE_LOG_LEVEL).toString();
    if (fileLogLevel.isEmpty()) {
        _settings->value(Settings::Logging::FILE_LOG_LEVEL) = Settings::Logging::Levels::INFO;
    } else {
        validateLogLevel(Settings::Logging::FILE_LOG_LEVEL, fileLogLevel);
    }

    if (_settings->value(Settings::Logging::LOG_FILE_SIZE).toInt() == 0) {
        _settings->setValue(Settings::Logging::LOG_FILE_SIZE, 1048576);
    }

    if (_settings->value(Settings::Logging::LOG_FILE_COUNT).toInt() == 0) {
        _settings->setValue(Settings::Logging::LOG_FILE_COUNT, 10);
    }

    if (_settings->value(Settings::Logging::LOG_FILE_DIRECTORY).toString().isEmpty()) {
        QString path = QDir::currentPath().append("/logs");
        _settings->setValue(Settings::Logging::LOG_FILE_DIRECTORY, path);
    }
}

void
Bot::validateLogLevel(QString property, QString logLevel) {
    QMetaEnum metaEnum = QMetaEnum::fromType<Settings::Logging::Levels>();
    if (metaEnum.keyToValue(logLevel.toUpper().toStdString().c_str()) < 0) {
        invalidEnumValue(property, logLevel, metaEnum);
    }
}

void
Bot::invalidEnumValue(QString property, QString value, QMetaEnum metaEnum) {
    qDebug().noquote() << QString("[%1]").arg(_settings->fileName()) << "\n";
    qDebug().noquote() << QString("Invalid %1: %2\n").arg(property, value);
    qDebug() << "Possible values:";
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        qDebug().noquote() << "\t" << metaEnum.key(i);
    }
    exit(1);
}

void
Bot::invalidDatabaseProperty(QString databaseType, QString propertyName) {
    QString fileName = QString("[%1]").arg(_settings->fileName());
    qDebug().noquote() << fileName << "\n";
    qDebug().noquote() << "Database Type: " << databaseType << "\n";
    qDebug().noquote() << QString("ERROR: Property \"%1\" cannot be blank.\n").arg(propertyName);
    exit(1);
}

void
Bot::initializeLogging() {
    try {
        QString path = _settings->value(Settings::Logging::LOG_FILE_DIRECTORY).toString();
        QDir dir = QDir(path);
        if (!(dir.exists())) {
            if (!(dir.mkpath("."))) {
               qDebug() << "Error creating log directory. . . exiting.";
               exit(1);
            }
        }

        std::vector<spdlog::sink_ptr> sinks;
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        int consoleLevel = getLogLevel(_settings->value(Settings::Logging::CONSOLE_LOG_LEVEL).toString());
        consoleSink->set_level(spdlog::level::level_enum(consoleLevel));
        sinks.push_back(consoleSink);

        QString filePath = dir.path().append("/bot.log");
        int logSize = _settings->value(Settings::Logging::LOG_FILE_SIZE).toInt();
        int logCount = _settings->value(Settings::Logging::LOG_FILE_COUNT).toInt();
        auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filePath.toStdString(), logSize, logCount);
        int fileLevel = getLogLevel(_settings->value(Settings::Logging::FILE_LOG_LEVEL).toString());
        fileSink->set_level(spdlog::level::level_enum(fileLevel));
        sinks.push_back(fileSink);

        auto logger = std::make_shared<spdlog::logger>(Settings::Logging::LOGGER.toStdString(), begin(sinks), end(sinks));
        logger->set_level(spdlog::level::trace); // Log granularity handled by specific sink values
        spdlog::register_logger(logger);
        _logger = logger;
    } catch (const spdlog::spdlog_ex& ex) {
        qDebug() << "Log initialization failed: " << ex.what();
        exit(1);
    }
}

int
Bot::getLogLevel(QString logLevel) {
    QMetaEnum metaEnum = QMetaEnum::fromType<Settings::Logging::Levels>();
    return metaEnum.keyToValue(logLevel.toUpper().toStdString().c_str());
}

void
Bot::run() {
    QUrl connectionUrl = buildConnectionUrl();
    GatewayService *connection = new GatewayService(QUrl(QStringLiteral("ws://127.0.0.1:1234")), nullptr);
    connection->moveToThread(&_gatewayThread);
    connect(&_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);
    connect(&_gatewayThread, &QThread::started, connection, &GatewayService::init);

    EventService *messageHandler = new EventService;
    messageHandler->moveToThread(&_messageServiceThread);
    connect(&_messageServiceThread, &QThread::finished, messageHandler, &QObject::deleteLater);
    connect(connection, &GatewayService::payloadReady, messageHandler, &EventService::processEvent);

    _messageServiceThread.start();
    _gatewayThread.start();
    _gatewayThread.setPriority(QThread::HighestPriority);
}

QUrl
Bot::buildConnectionUrl() {
    QUrl url("url");
    return url;
}
