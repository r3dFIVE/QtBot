#include "clientstatus.h"

#include <jsonutils.h>

QString
ClientStatus::getDesktop() {
    return desktop;
}

void
ClientStatus::setDesktop(QString desktop) {
    this->desktop = desktop;
}

QString
ClientStatus::getMobile() {
    return mobile;
}

void
ClientStatus::setMobile(QString mobile) {
    this->mobile = mobile;
}

QString
ClientStatus::getWeb() {
    return web;
}

void
ClientStatus::setWeb(QString web) {
    this->web = web;
}

void
ClientStatus::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
ClientStatus::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}

