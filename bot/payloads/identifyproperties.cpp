#include "identifyproperties.h"

void
IdentifyProperties::read(const QJsonObject &jsonObject) {
    $os = jsonObject[OS].toString();
    $browser = jsonObject[BROWSER].toString();
    $device = jsonObject[DEVICE].toString();
}

void
IdentifyProperties::write(QJsonObject &jsonObject) {
    jsonObject[OS] = $os;
    jsonObject[BROWSER] = $browser;
    jsonObject[DEVICE] = $device;
}
