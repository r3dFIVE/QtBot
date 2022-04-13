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
#include "payloads/embed.h"

const QString IBinding::BINDING_TYPE = "binding_type";
const QString IBinding::BINDING_TYPE_COMMAND = "command";
const QString IBinding::BINDING_TYPE_GATEWAY = "gateway";
const QString IBinding::BINDING_TYPE_TIMED = "timed";
const QString IBinding::BINDING_NAME = "binding_name";
const QString IBinding::FUNCTION = "function";
const QString IBinding::IGNORE_ADMIN = "ignore_admin";
const QString IBinding::DESCRIPTION = "description";
const QString IBinding::DESCRIPTION_SHORT = "short_description";
const QString IBinding::NO_DESCRIPTION = "< No Description >";
const QString IBinding::ADMIN_ONLY = "admin_only";


bool
IBinding::validateFunctionMapping(const QMetaObject &metaObject) const {

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

const QString
IBinding::getDescription() const {
    return _baseProperties->description.isEmpty()
            ? getDescriptionShort() : _baseProperties->description;
}

void
IBinding::setBaseProperties(QSharedPointer<IBindingProperties> properties) {
    _baseProperties = properties;
}

const QString
IBinding::getDescriptionShort() const {
    QString descriptionShort;

    if (!_baseProperties->descriptionShort.isEmpty()) {
        descriptionShort = _baseProperties->descriptionShort;
    } else if (!_baseProperties->description.isEmpty()) {
        descriptionShort = _baseProperties->description;
    } else {
        descriptionShort = IBinding::NO_DESCRIPTION;
    }

    return descriptionShort.left(Embed::DECRIPTION_SHORT_MAX_LENGTH);
}

const QString&
IBinding::getName() const {
    return _baseProperties->name;
}

bool
IBinding::isAdminOnly() const {
    return _baseProperties->adminOnly;
}

bool
IBinding::ignoreAdmin() {
    return _baseProperties->ignoreAdmin;
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

void
IBinding::setFunctionMapping(const IBotJob::FunctionMapping &functionMapping) {
    _functionMapping = functionMapping;
}
