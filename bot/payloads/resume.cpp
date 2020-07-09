#include "resume.h"

#include "util/serializationutils.h"

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
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
Resume::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
