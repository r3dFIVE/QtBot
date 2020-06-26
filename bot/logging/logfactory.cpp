#include "logfactory.h"
#include "globals.h"

#include <QVariant>

Logger* LogFactory::_logger = nullptr;

LogFactory::LogFactory() { }

LogFactory::~LogFactory() { delete _logger; }

Logger*
LogFactory::getLogger() {
    if (_logger == nullptr) {
        qDebug("Logger not initialized, using default console logging...");
        LogContext ctx;
        _logger = new Logger(ctx);
    }

    return _logger;
}

Logger*
LogFactory::init(QSharedPointer<Settings> settings) {

    LogContext ctx;
    ctx.maxFileSize = settings->value(SettingsParam::Logging::LOG_FILE_SIZE).toInt();
    ctx.maxRolloverFiles = settings->value(SettingsParam::Logging::LOG_ROLLOVER_COUNT).toInt();
    ctx.directoryPath = settings->value(SettingsParam::Logging::LOG_FILE_DIRECTORY).toString();
    ctx.fileName = settings->value(SettingsParam::Logging::LOG_FILE_NAME).toString();
    ctx.consoleLogLevel = LogContext::LogLevel(settings->value(SettingsParam::Logging::CONSOLE_LOG_LEVEL).toInt());
    ctx.fileLogLevel = LogContext::LogLevel(settings->value(SettingsParam::Logging::FILE_LOG_LEVEL).toInt());

    if (_logger == nullptr) {
        _logger = new Logger(ctx);
    }

    return _logger;
}
