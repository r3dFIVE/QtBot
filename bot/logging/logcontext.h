#ifndef LOGCONTEXT_H
#define LOGCONTEXT_H

#include <QCoreApplication>
#include <QObject>
#include <QString>

class LogContext : public QObject {
    Q_OBJECT

public:
    LogContext () {}

    LogContext(const LogContext& ctx) {
        fileName = ctx.fileName;
        directoryPath = ctx.directoryPath;
        maxRolloverFiles = ctx.maxRolloverFiles;
        maxFileSize = ctx.maxFileSize;
        consoleLogLevel = ctx.consoleLogLevel;
        fileLogLevel = ctx.fileLogLevel;
    }

    void operator=(const LogContext& ctx) {
        fileName = ctx.fileName;
        directoryPath = ctx.directoryPath;
        maxRolloverFiles = ctx.maxRolloverFiles;
        maxFileSize = ctx.maxFileSize;
        consoleLogLevel = ctx.consoleLogLevel;
        fileLogLevel = ctx.fileLogLevel;
    }

    enum LogLevel {
        OFF = 0,
        FATAL,
        CRITICAL,
        WARNING,
        INFO,
        DEBUG,
        TRACE
    };

    QString getPathWithName() {
        return directoryPath + "/" + fileName;
    }

    bool fileLoggingEnabled(LogLevel level) {
        return fileLogLevel >= level;
    }

    bool consoleLoggingEnabled(LogLevel level) {
        return consoleLogLevel >= level;
    }

    bool loggingEnabled() {
        return consoleLogLevel != LogLevel::OFF || fileLogLevel != LogLevel::OFF;
    }

    QString directoryPath = qApp->applicationDirPath();
    QString fileName = "bot.log";
    int maxFileSize = 1000000; //10 MB
    int maxRolloverFiles = 10;
    LogLevel consoleLogLevel = DEBUG;
    LogLevel fileLogLevel = DEBUG;

    Q_ENUM(LogLevel)
};

Q_DECLARE_METATYPE(LogContext::LogLevel)

#endif // LOGCONTEXT_H
