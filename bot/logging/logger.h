#ifndef LOGGER_H
#define LOGGER_H

#include "logworker.h"

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT

public:
    void trace(QString message);
    void info(QString message);
    void debug(QString message);
    void warning(QString message);
    void critical(QString message);
    void fatal(QString message);

signals:
    void logEvent(LogContext::LogLevel level, QString message);

private:
    explicit Logger(LogContext ctx, QObject *parent = nullptr);
    ~Logger();

    QThread *_thread;
    LogWorker *_worker;

    friend class LogFactory;
};

#endif // LOGGER_H
