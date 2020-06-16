#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "logger.h"

#include <QString>
#include <settings.h>
#include <QSharedPointer>

class LogFactory
{
private:
    static Logger* _logger;
    LogFactory();
    ~LogFactory();

public:
    static Logger* getLogger();
    static void init(QSharedPointer<Settings> settings);
};

#endif // LOGSERVICE_H
