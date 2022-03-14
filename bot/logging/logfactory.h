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

#ifndef LOGFACTORY_H
#define LOGFACTORY_H

#include "logger.h"
#include "logworker.h"

#include <QString>
#include <QSharedPointer>

#include "util/settings.h"

class LogFactory
{
    static LogWorker *_worker;
    static QHash<QString, Logger*> _loggers;

public:
    static Logger* getLogger(QString prefix = QString());
    static Logger *getLogger(QObject *parent);
    static void cleanup();
    static void init(LogWorker *worker);

};

#endif // LOGFACTORY_H
