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
#include "util/globals.h"

#include <QVariant>

Logger* LogFactory::_logger = nullptr;

LogFactory::LogFactory() { }

LogFactory::~LogFactory() { delete _logger; }

Logger*
LogFactory::getLogger() {
    if (_logger == nullptr) {

        qDebug("Logger not initialized, using default console logging...");

        LogContext ctx;

        _logger = new Logger(ctx);
    }

    return _logger;
}

Logger*
LogFactory::init(QSharedPointer<Settings> settings) {

    LogContext ctx;

    ctx.maxFileSize = settings->value(SettingsParam::Logging::LOG_FILE_SIZE).toInt();

    ctx.maxRolloverFiles = settings->value(SettingsParam::Logging::LOG_ROLLOVER_COUNT).toInt();

    ctx.directoryPath = settings->value(SettingsParam::Logging::LOG_FILE_DIRECTORY).toString();

    ctx.fileName = settings->value(SettingsParam::Logging::LOG_FILE_NAME).toString();

    ctx.consoleLogLevel = LogContext::LogLevel(settings->value(SettingsParam::Logging::CONSOLE_LOG_LEVEL).toInt());

    ctx.fileLogLevel = LogContext::LogLevel(settings->value(SettingsParam::Logging::FILE_LOG_LEVEL).toInt());

    if (_logger == nullptr) {
        _logger = new Logger(ctx);
    }

    return _logger;
}
