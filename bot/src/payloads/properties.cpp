#include "properties.h"

void
Properties::read(const QJsonObject &jsonObject) {
    $os = jsonObject[OS].toString();
    $browser = jsonObject[BROWSER].toString();
    $device = jsonObject[DEVICE].toString();
}

void
Properties::write(QJsonObject &jsonObject) const {
    jsonObject[OS] = $os;
    jsonObject[BROWSER] = $browser;
    jsonObject[DEVICE] = $device;
}
