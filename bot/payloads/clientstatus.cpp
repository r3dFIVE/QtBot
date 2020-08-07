#include "clientstatus.h"

const QString ClientStatus::DESKTOP = "desktop";
const QString ClientStatus::MOBILE = "mobile";
const QString ClientStatus::WEB = "web";

QJsonValue
ClientStatus::getDesktop() const {
    return _jsonObject[DESKTOP];
}

void
ClientStatus::setDesktop(const QJsonValue &desktop) {
    _jsonObject[DESKTOP] = desktop;
}

QJsonValue
ClientStatus::getMobile() const {
    return _jsonObject[MOBILE];
}

void
ClientStatus::setMobile(const QJsonValue &mobile) {
    _jsonObject[MOBILE] = mobile;
}

QJsonValue
ClientStatus::getWeb() const {
    return _jsonObject[WEB];
}

void
ClientStatus::setWeb(const QJsonValue &web) {
    _jsonObject[WEB] = web;
}
