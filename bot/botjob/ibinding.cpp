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

#include "ibinding.h"


const QString IBinding::BINDING_TYPE = "binding_type";
const QString IBinding::BINDING_TYPE_COMMAND = "command";
const QString IBinding::BINDING_TYPE_GATEWAY = "gateway";
const QString IBinding::BINDING_TYPE_TIMED = "timed";
const QString IBinding::FUNCTION = "function";
const QString IBinding::DESCRIPTION = "description";
const QString IBinding::IGNORE_ADMIN = "ignore_admin";
const QString IBinding::BINDING_NAME = "binding_name";


bool IBinding::validateFunctionMapping(const QMetaObject &metaObject) const {


    if (_functionMapping.first.isEmpty() || !_functionMapping.second) {
        _logger->warning(QString("Invalid command mapping. First: %1, Second: %2... Discarding binding.")
                         .arg(_functionMapping.first.isEmpty() )
                         .arg(!_functionMapping.second ? "nullptr" : _functionMapping.second->objectName()));

        return false;
    }

    if (!isValidParam(IBinding::FUNCTION, _functionMapping.first)) {
        return false;
    }

    QByteArray functionName = QString(_functionMapping.first + "(QVariant)").toUtf8();

    if (metaObject.indexOfMethod(functionName) < 0) {
        _logger->warning(QString("\"%1\" function was not defined in this script... Discarding binding.")
                         .arg(_functionMapping.first));

        return false;
    }

    return true;
}


bool
IBinding::isAdminOnly() const {
    return _adminOnly;
}

void
IBinding::setAdminOnly(const bool adminOnly) {
    _adminOnly = adminOnly;
}

bool
IBinding::ignoreAdmin() {
    return _ignoreAdmin;
}

void
IBinding::setIgnoreAdmin(bool ignoreAdmin) {
    _ignoreAdmin = ignoreAdmin;
}

bool
IBinding::isValidParam(const QString &name, const QString &value) const {
    if (value.isEmpty()) {
        _logger->warning(QString("%1 cannot be empty.").arg(name));

        return false;
    }

    if (value.simplified().contains(" ")) {
        _logger->warning(QString("%1 parameters can not have any whitespace characters: %2").arg(value));

        return false;
    }

    bool isNumber = false;

    value.toDouble(&isNumber);

    if (isNumber) {
        _logger->warning(QString("%1 parameters must not be only numeric values: %2").arg(name).arg(value));

        return false;
    }

    return true;
}


IBotJob::FunctionMapping
IBinding::getFunctionMapping() const {
    return _functionMapping;
}

QString
IBinding::getDescription() const {
    return _description;
}

void
IBinding::setDescription(const QString &description) {
    _description = description;
}

void
IBinding::setFunctionMapping(const IBotJob::FunctionMapping &functionMapping) {
    _functionMapping = functionMapping;
}

QString
IBinding::getBindingName() const {
    return _bindingName;
}

void
IBinding::setBindingName(const QString &bindingName) {
    _bindingName = bindingName;
}
