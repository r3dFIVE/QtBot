#include "gatewaybinding.h"

#include "util/enumutils.h"


const QString GatewayBinding::GATEWAY_EVENT = "gateway_event";

GatewayBinding::GatewayBinding(const QString &eventType) {
    setEventName(eventType);
}

GatewayBinding::GatewayBinding(const GatewayBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _eventName = other._eventName;
}

GatewayBinding
&GatewayBinding::operator=(const GatewayBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _eventName = other._eventName;

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
