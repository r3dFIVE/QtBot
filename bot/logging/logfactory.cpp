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

#include "logfactory.h"

#include <QThread>

LogWorker *LogFactory::_worker = nullptr;
QHash<QString, Logger*> LogFactory::_loggers = QHash<QString, Logger*>();

Logger*
LogFactory::getLogger(QObject *parent) {
    return getLogger(parent->metaObject()->className());
}

Logger*
LogFactory::getLogger(QString loggerName) {
    if (!_loggers.contains(loggerName)) {
        Logger *logger = new Logger(loggerName);

        QObject::connect(logger, &Logger::logEvent, _worker, &LogWorker::logEvent);

        _loggers[loggerName] = logger;
    }

    return _loggers[loggerName];
}

void
LogFactory::init(LogWorker *worker) {
    _worker = worker;
}

void
LogFactory::cleanup() {
    for (Logger *logger : _loggers) {
        delete logger;
    }
}


