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
 *
 */

#ifndef LOGCONTEXT_H
#define LOGCONTEXT_H

#include <QCoreApplication>
#include <QObject>
#include <QString>

class LogContext : public QObject {
    Q_OBJECT


public:
    LogContext (QObject *parent = nullptr) : QObject(parent) {}

    LogContext(const LogContext& ctx) : QObject(ctx.parent()) {
        if (this == &ctx) {
            return;
        }

        fileName = ctx.fileName;

        directoryPath = ctx.directoryPath;

        maxRolloverFiles = ctx.maxRolloverFiles;

        maxFileSize = ctx.maxFileSize;

        consoleLogLevel = ctx.consoleLogLevel;

        fileLogLevel = ctx.fileLogLevel;
    }

    LogContext& operator=(const LogContext& other) {
        if (this == &other) {
            return *this;
        }

        fileName = other.fileName;

        directoryPath = other.directoryPath;

        maxRolloverFiles = other.maxRolloverFiles;

        maxFileSize = other.maxFileSize;

        consoleLogLevel = other.consoleLogLevel;

        fileLogLevel = other.fileLogLevel;

        return *this;
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
