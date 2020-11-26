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
