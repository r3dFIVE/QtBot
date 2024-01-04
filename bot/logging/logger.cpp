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

#include "logger.h"

#include <QThread>

#include "logutils.h"

Logger::Logger(const QString &loggerName, QObject *parent) : QObject {parent} {
    _loggerName = loggerName;
}

void
Logger::trace(const QString &message) {
    emit logEvent(TRACE, message, _loggerName);
}

void
Logger::info(const QString &message) {
    emit logEvent(INFO, message, _loggerName);
}

void
Logger::debug(const QString &message) {
    emit logEvent(DEBUG, message, _loggerName);
}

void
Logger::warning(const QString &message) {
    emit logEvent(WARNING, message, _loggerName);
}

void
Logger::critical(const QString &message) {
    emit logEvent(CRITICAL, message, _loggerName);
}

void
Logger::fatal(const QString &message) {
    emit logEvent(FATAL, message, _loggerName);
}
