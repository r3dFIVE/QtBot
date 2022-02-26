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
    static const QString BOT_IMPORT_IDENTIFIER;
    static const QString BOT_TYPE_IDENTIFIER;
    static const int BOT_API_MINOR_VERSION;
    static const int BOT_API_MAJOR_VERSION;    
    static const QString FILE_OPEN_MODE_IDENTIFIER;
    static const QString HTML_TAG_TYPE_IDENTIFIER;
    static const QString NETWORK_REQUEST_IDENTIFIER;
    static const QString SQL_IDENTIFIER;
    static const QString NO_CREATABLE_ENUM;

    Bot();
    void run();
};

#endif // BOT_H
