/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "logworker.h"

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QRegularExpression>
#include <iostream>

#include "util/settings.h"

LogWorker::LogWorker(QObject *parent) : QObject(parent) {
    _maxFileSize = Settings::logFileSize();

    _maxRolloverFiles = Settings::logRolloverCount();

    _directoryPath = Settings::logFileDirectory();

    _fileName = Settings::logFileName();

    _consoleLogLevel = Logger::LogLevel(Settings::consoleLogLevel());

    _fileLogLevel = Logger::LogLevel(Settings::fileLogLevel());

    if (fileLoggingEnabled(Logger::OFF)) {
        initLogFile();
    }
}

QString
LogWorker::getPathWithName() const {
    return _directoryPath + "/" + _fileName;
}

bool
LogWorker::fileLoggingEnabled(Logger::LogLevel level) {
    return _fileLogLevel >= level;
}

bool
LogWorker::consoleLoggingEnabled(Logger::LogLevel level) {
    return _consoleLogLevel >= level;
}

bool
LogWorker::loggingEnabled() {
    return _consoleLogLevel != Logger::OFF || _fileLogLevel != Logger::OFF;
}

void
LogWorker::initLogFile() {
    QDir logDir(_directoryPath);

    if (!logDir.exists()) {
        logDir.mkdir(".");
    }

    _logFile.setFileName(getPathWithName());

    if (!_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        disableFileLogging();

        return;
    } else {
        checkLogFile();
    }
}

void
LogWorker::disableFileLogging() {
    qDebug() << "Error opening " + _fileName;

    qDebug() << "Disabling file logging.";

    _fileLogLevel = Logger::LogLevel::OFF;
}

void
LogWorker::checkLogFile() {
    if (_maxFileSize == 0) {
        return;
    }

    if (_logFile.size() > _maxFileSize) {
        rolloverLog();
    }
}

void
LogWorker::rolloverLog() {
    _logFile.close();

    QDir logDir(_directoryPath);

    QMap<int, QStringList> logNameByNumber;

    int maxFilesRegex = QString::number(_maxRolloverFiles).length();

    for ( auto entry : logDir.entryList()) {
        QRegularExpression logExpression(QString("^%1$").arg(_fileName));

        QRegularExpression logWithNumberExpression(QString("^%1.[0-9]{1,%2}$").arg(_fileName).arg(maxFilesRegex));

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

        QFile existingLogFile(_directoryPath + "/" + fullFileName);

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

        if (logNumber > _maxRolloverFiles) {
            existingLogFile.remove();
        } else {
            existingLogFile.rename(_directoryPath + "/" + newFileName);

            existingLogFile.close();
        }
    }

    if (!_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        disableFileLogging();
    }
}

void
LogWorker::logEvent(Logger::LogLevel level, QString message, QString loggerName) {
    if (loggingEnabled()) {
        message += "\n";

        QString logLevel = QVariant::fromValue(level).toString();

        QString dateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");

        QString logString = QString("[%1][%2][%3]: %4")
                .arg(dateTime)
                .arg(logLevel)
                .arg(loggerName)                
                .arg(message);

        if (consoleLoggingEnabled(level)) {
            std::cerr << logString.toStdString();
        }

        if (fileLoggingEnabled(level)) {
            checkLogFile();

            _logFile.write(logString.toUtf8().data());

            _logFile.flush();
        }
    }
}
