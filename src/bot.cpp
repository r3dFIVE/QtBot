#include "bot.h"
#include "eventservice.h"
#include "globals.h"

#include <QDir>
#include <QMetaEnum>


Bot::Bot(QString path)
{   
    _settings = QSharedPointer<SettingsService>(new SettingsService(path));

    initializeLogging();

    _logger->info("QtBot is now starting. . .");

//    qDebug() << QSysInfo::kernelType();
//    qDebug() << _settings->isWritable();
//    qDebug() << _settings->value("test_val").toBool();
//    qDebug() << _settings->value("bot_token").toString();
//    qDebug() << _settings->value("invalid_token").isNull();

    qRegisterMetaType<QSharedPointer<JsonSerializeable>>();
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
