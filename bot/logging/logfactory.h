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

#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "logger.h"

#include <QString>
#include <util/settings.h>
#include <QSharedPointer>

class LogFactory
{
private:
    static Logger* _logger;
    LogFactory();
    ~LogFactory();

public:
    static Logger* getLogger();
    static Logger* init(QSharedPointer<Settings> settings);
};

#endif // LOGSERVICE_H
