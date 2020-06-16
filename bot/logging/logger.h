#ifndef LOGGER_H
#define LOGGER_H

#include "logworker.h"

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT

public:
    void trace(QString event);
    void info(QString event);
    void debug(QString event);
    void warning(QString event);
    void critical(QString event);
    void fatal(QString event);

signals:
    void logEvent(LogContext::LogLevel level, QString event);

private:
    explicit Logger(LogContext ctx, QObject *parent = nullptr);
    ~Logger();

    QThread *_thread;
    LogWorker *_worker;

    friend class LogFactory;
};

#endif // LOGGER_H
