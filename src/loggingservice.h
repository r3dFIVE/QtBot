#ifndef LOGGINGSERVICE_H
#define LOGGINGSERVICE_H

#include "settingsservice.h"
#include "spdlog/spdlog.h"

#include <QSharedPointer>

typedef std::shared_ptr<spdlog::logger> Logger;

class LoggingService
{
public:
    static void initializeLogging(QSharedPointer<SettingsService> settings);
    static Logger getLogger();

private:
    static int getLogLevel(QString level);
};

#endif // LOGGINGSERVICE_H
