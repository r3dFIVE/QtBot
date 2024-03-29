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


GatewayBinding::GatewayBinding(const QString &eventName) {
    _gatewayProperties->eventName = eventName;
}

GatewayBinding::GatewayBinding(const GatewayBinding &other) : IBinding{other._baseProperties} {
    if (this == &other) {
        return;
    }

    copy(other);
}

GatewayBinding
&GatewayBinding::operator=(const GatewayBinding &other) {
    if (this == &other) {
        return *this;
    }

    copy(other);

    return *this;
}

void
GatewayBinding::setGatewayProperties(QSharedPointer<GatewayBindingProperties> properties) {
    _gatewayProperties = properties;
}

void
GatewayBinding::copy(const GatewayBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _baseProperties = other._baseProperties;

    _gatewayProperties = other._gatewayProperties;
}

QString
GatewayBinding::getEventName() const {
    return _gatewayProperties->eventName;
}


bool GatewayBinding::isValid(const QMetaObject &metaObject) const {
    if (!isValidParam(GatewayBinding::BINDING_NAME, _baseProperties->name)) {
        return false;
    }

    if (!validateFunctionMapping(metaObject)) {
        return false;
    }

    int _gatewayEventCode = EnumUtils::keyToValue<GatewayEvent::Event>(_gatewayProperties->eventName);

    if (_gatewayEventCode < 0) {
        _logger->warning("Invalid Gateway event type specified... Discarding binding.");

        return false;
    }

    return true;
}
