#include "loggingservice.h"
#include "globals.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include <QDir>
#include <QVariant>
#include <QMetaEnum>
#include <QDebug>

#include <spdlog/logger.h>

void
LoggingService:: initializeLogging(QSharedPointer<SettingsService> _settings) {
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
    } catch (const spdlog::spdlog_ex& ex) {
        qDebug() << "Log initialization failed: " << ex.what();
        exit(1);
    }
}

int
LoggingService::getLogLevel(QString logLevel) {
    QMetaEnum metaEnum = QMetaEnum::fromType<Settings::Logging::Levels>();
    return metaEnum.keyToValue(logLevel.toUpper().toStdString().c_str());
}

Logger
LoggingService::getLogger() {
    return spdlog::get(Settings::Logging::LOGGER.toStdString());
}
