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

#include "gatewaybinding.h"

#include "util/enumutils.h"


const QString GatewayBinding::GATEWAY_EVENT = "gateway_event";
const QString GatewayBinding::SINGLETON = "singleton";


GatewayBinding::GatewayBinding(const QString &eventName) {
    _eventName = eventName;
}

GatewayBinding::GatewayBinding(const GatewayBinding &other) {
    if (this == &other) {
        return;
    }

    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _ignoreAdmin = other._ignoreAdmin;

    _description = other._description;

    _eventName = other._eventName;

    _bindingName = other._bindingName;
}

GatewayBinding
&GatewayBinding::operator=(const GatewayBinding &other) {
    if (this == &other) {
        return *this;
    }

    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _ignoreAdmin = other._ignoreAdmin;

    _description = other._description;

    _eventName = other._eventName;

    _bindingName = other._bindingName;

    return *this;
}

QString
GatewayBinding::getEventName() const {
    return _eventName;
}

void GatewayBinding::setEventName(const QString &eventName) {
    _eventName = eventName;
}

bool GatewayBinding::isValid(const QMetaObject &metaObject) const {
    if (!isValidParam(GatewayBinding::BINDING_NAME, _bindingName)) {
        return false;
    }

    if (!validateFunctionMapping(metaObject)) {
        return false;
    }

    int _gatewayEventCode = EnumUtils::keyToValue<GatewayEvent::Event>(_eventName);

    if (_gatewayEventCode < 0) {
        _logger->warning("Invalid Gateway event type specified... Discarding binding.");

        return false;
    }

    return true;
}
