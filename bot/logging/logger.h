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
