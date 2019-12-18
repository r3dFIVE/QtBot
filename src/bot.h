#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>
#include <spdlog/logger.h>
#include "gatewayservice.h"
#include "settingsservice.h"


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
    Logger _logger;

    int getLogLevel(QString property);
    void initializeLogging();
};

#endif // BOT_H
