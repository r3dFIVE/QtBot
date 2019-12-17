#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>
#include "gatewayservice.h"
#include "settingsservice.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

class Bot : public QObject
{
    Q_OBJECT

public:
    Bot(QString settings);
    void run();

private:
    QThread _gatewayThread;
    QThread _messageServiceThread;
    QSharedPointer<SettingsService> _settings;
    std::shared_ptr<spdlog::logger> _logger;

    QUrl buildConnectionUrl();
    int getLogLevel(QString property);
    void initializeLogging();
};

#endif // BOT_H
