#include "identifyproperties.h"


const QString IdentifyProperties::OS = "$os";
const QString IdentifyProperties::BROWSER = "$browser";
const QString IdentifyProperties::DEVICE = "$device";

IdentifyProperties::IdentifyProperties() {
    _jsonObject[OS] = $os;
    _jsonObject[BROWSER] = $browser;
    _jsonObject[DEVICE] = $device;
}

QJsonValue
IdentifyProperties::getOS() const {
    return _jsonObject[OS];
}

QJsonValue
IdentifyProperties::getBrowser() const {
    return _jsonObject[BROWSER];
}

QJsonValue
IdentifyProperties::getDevice() const {
    return _jsonObject[BROWSER];
}

void
IdentifyProperties::setBrowser(const QJsonValue &browser) {
    _jsonObject[BROWSER] = browser;
}

void
IdentifyProperties::setDevice(const QJsonValue &device) {
    _jsonObject[DEVICE] = device;
}

void
IdentifyProperties::setOS(const QJsonValue &os) {
    _jsonObject[OS] = os;
}

