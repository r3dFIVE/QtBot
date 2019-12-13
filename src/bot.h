#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>
#include "gatewayservice.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

class Bot : public QObject
{
    Q_OBJECT

public:
    Bot(QSharedPointer<QSettings> settings);
    void run();

private:
    QThread _gatewayThread;
    QThread _messageServiceThread;
    QSharedPointer<QSettings> _settings;
    std::shared_ptr<spdlog::logger> _logger;

    QUrl buildConnectionUrl();
    int getLogLevel(QString property);
    void validateSettings();
    void validateConnectionSettings();
    void validateDatabaseSettings();
    void validateLoggingSettings();
    void validateLogLevel(QString property, QString logLevel);
    void initializeLogging();
    void invalidDatabaseProperty [[ noreturn ]] (QString databaseType, QString propertyName);
    void invalidEnumValue [[ noreturn ]] (QString property, QString value, QMetaEnum metaEnum);
};

#endif // BOT_H
