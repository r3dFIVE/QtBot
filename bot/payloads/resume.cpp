#include "resume.h"

#include "util/jsonutils.h"

QString
Resume::getToken() {
    return token;
}

void
Resume::setToken(QString token) {
    this->token = token;
}

QString
Resume::getSessionId() {
    return session_id;
}

void
Resume::setSessionId(QString session_id) {
    this->session_id = session_id;
}

int
Resume::getSeq() {
    return seq;
}

void
Resume::setSeq(int seq) {
    this->seq = seq;
}

void
Resume::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
Resume::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
