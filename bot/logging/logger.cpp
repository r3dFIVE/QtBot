/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "logger.h"

#include <QThread>

Logger::Logger(LogContext ctx, QObject *parent) : QObject (parent) {
    _thread = new QThread(this);

    _worker = new LogWorker(ctx);

    _worker->moveToThread(_thread);

    connect(this, &Logger::logEvent, _worker, &LogWorker::logEvent);

    connect(_thread, &QThread::finished, _worker, &QObject::deleteLater);

    _thread->start();
}

Logger::~Logger() {
    _thread->quit();

    _thread->wait();
}

void
Logger::trace(QString message) {
    logEvent(LogContext::LogLevel::TRACE, message);
}

void
Logger::info(QString message) {
    logEvent(LogContext::LogLevel::INFO, message);
}

void
Logger::debug(QString message) {
    logEvent(LogContext::LogLevel::DEBUG, message);
}

void
Logger::warning(QString message) {
    logEvent(LogContext::LogLevel::WARNING, message);
}

void
Logger::critical(QString message) {
    logEvent(LogContext::LogLevel::CRITICAL, message);
}

void
Logger::fatal(QString message) {
    logEvent(LogContext::LogLevel::FATAL, message);
}
