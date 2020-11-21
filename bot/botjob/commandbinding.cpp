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

#include "commandbinding.h"


const QString CommandBinding::COMMAND = "command";
const QString CommandBinding::ADMIN_ONLY = "admin_only";

CommandBinding::CommandBinding(const QString &commandName, const IBotJob::FunctionMapping &functionMapping) {
    _commandName = commandName;

    _functionMapping = functionMapping;
}

CommandBinding::CommandBinding(const CommandBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _commandName = other._commandName;

    _adminOnly = other._adminOnly;
}

CommandBinding
&CommandBinding::operator=(const CommandBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _commandName = other._commandName;

    _adminOnly = other._adminOnly;

    return *this;
}

bool
CommandBinding::isAdminOnly() const {
    return _adminOnly;
}

void
CommandBinding::setAdminOnly(const bool adminOnly) {
    _adminOnly = adminOnly;
}

QString
CommandBinding::getCommandName() const {
    return _commandName;
}

void
CommandBinding::setCommandName(const QString &commandName) {
    _commandName = commandName;
}

bool
CommandBinding::isValid(const QMetaObject &metaObject) const {
    if (!validateFunctionMapping(metaObject)) {
        return false;
    }

    if (_commandName.isEmpty()) {
        _logger->warning(QString("\"%1\" property is not set for command binding for function \"%2\"... Discarding binding.")
                         .arg(COMMAND)
                         .arg(_functionMapping.first));

        return false;
    }

    return true;
}
