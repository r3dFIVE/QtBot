#include "logcontext.h"
#include "logworker.h"
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QMetaEnum>
#include <QRegularExpression>


LogWorker::LogWorker(LogContext ctx, QObject *parent)
    : QObject(parent), _ctx(ctx) {

    if (_ctx.fileLoggingEnabled(LogContext::LogLevel::OFF)) {
        initLogFile();
    }
}

void
LogWorker::initLogFile() {
    QDir logDir(_ctx.directoryPath);
    if (!logDir.exists()) {
        logDir.mkdir(".");
    }

    _logFile.setFileName(_ctx.getPathWithName());
    if (!_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        disableFileLogging();
        return;
    } else {
        checkLogFile();
    }
}

void
LogWorker::disableFileLogging() {
    qDebug() << "Error opening " + _ctx.fileName;
    qDebug() << "Disabling file logging.";
    _ctx.fileLogLevel = LogContext::LogLevel::OFF;
}

void
LogWorker::checkLogFile() {
    if (_ctx.maxFileSize == 0) {
        return;
    }

    if (_logFile.size() > _ctx.maxFileSize) {
        rolloverLog();
    }
}

void
LogWorker::rolloverLog() {
    _logFile.close();
    QDir logDir(_ctx.directoryPath);
    QMap<int, QStringList> logNameByNumber;
    int maxFilesRegex = QString::number(_ctx.maxRolloverFiles).length();

    for ( auto entry : logDir.entryList()) {
        QRegularExpression logExpression(QString("^%1$").arg(_ctx.fileName));
        QRegularExpression logWithNumberExpression(QString("^%1.[0-9]{1,%2}$").arg(_ctx.fileName).arg(maxFilesRegex));

        if (logExpression.match(entry).hasMatch() || logWithNumberExpression.match(entry).hasMatch()) {
            QStringList logTokens = entry.split(".");
            int logNumber = logTokens.back().toInt();
            logNameByNumber[logNumber] = logTokens;
        }
    }

    QMapIterator<int, QStringList> logIterator(logNameByNumber);
    logIterator.toBack();

    while (logIterator.hasPrevious()) {
        logIterator.previous();
        int logNumber = logIterator.key();
        QStringList logTokens = logIterator.value();
        QString partialFileName = logTokens.front();
        QString suffix = logTokens.size() > 1 ? logTokens.back() : "";

        //Rebuild the fileName if it has multiple dots (.) eg. some.log.file
        for (int i = 1; i < logTokens.size() - 1; ++i) {
            partialFileName += "." + logTokens[i];
        }

        QString fullFileName = logTokens.size() > 1 ? partialFileName + "." + logTokens.back() : partialFileName;
        QFile existingLogFile(_ctx.directoryPath + "/" + fullFileName);

        if (!existingLogFile.open(QIODevice::ReadWrite | QIODevice::ExistingOnly)) {
            qDebug() << "Cant open file for renaming.";
            disableFileLogging();
            return;
        }

        QString newFileName = partialFileName;

        if (logNumber == 0) {
            if (suffix.isEmpty()) {
                newFileName += ".1";
            } else {
                newFileName += QString(".%1.1").arg(suffix);
            }
        } else {
            newFileName += "." + QString::number(++logNumber);
        }

        if (logNumber > _ctx.maxRolloverFiles) {
            existingLogFile.remove();
        } else {
            existingLogFile.rename(_ctx.directoryPath + "/" + newFileName);
            existingLogFile.close();
        }
    }

    if (!_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        disableFileLogging();
    }
}

void
LogWorker::logEvent(LogContext::LogLevel level, QString event) {
    if (_ctx.loggingEnabled()) {
        event += "\n";

        QString logLevel = QVariant::fromValue(level).toString();
        QString dateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");
        QString logString = QString("[%1][%2]: %3").arg(dateTime).arg(logLevel).arg(event);

        if (_ctx.consoleLoggingEnabled(level)) {
            fprintf(stderr, "%s", logString.toUtf8().data());
        }

        if (_ctx.fileLoggingEnabled(level)) {
            checkLogFile();
            _logFile.write(logString.toUtf8().data());
            _logFile.flush();
        }
    }
}
