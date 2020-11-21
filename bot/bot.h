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

#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>

#include "logging/logfactory.h"
#include "gateway.h"
#include "botjob/scriptbuilder.h"
#include "util/settings.h"

class GuildEntity;
class ScriptBuilder;

class Bot : public QObject
{
    Q_OBJECT    

    QThread _gatewayThread;
    QThread _eventHandlerThread;
    QThread _entityManagerThread;

    Logger* _logger;
    ScriptBuilder *_scriptBuilder;

public:
    Bot();
    void run(QSharedPointer<Settings> settings);
};

#endif // BOT_H
