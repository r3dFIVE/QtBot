#ifndef LOGWORKER_H
#define LOGWORKER_H


#include "logcontext.h"

#include <QFile>
#include <QObject>

class LogWorker : public QObject
{
    Q_OBJECT

private:
    LogWorker(const LogContext &ctx, QObject *parent = nullptr);
    ~LogWorker() {}
    void checkLogFile();
    void disableFileLogging();
    void initLogFile();
    void rolloverLog();

    QFile _logFile;
    LogContext _ctx;

public slots:
    void logEvent(LogContext::LogLevel level, QString message);

    friend class Logger;
};


#endif // LOGWORKER_H
