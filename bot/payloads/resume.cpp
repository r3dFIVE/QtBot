#include "resume.h"


const QString Resume::TOKEN = "token";
const QString Resume::SESSION_ID = "session_id";
const QString Resume::SEQ = "seq";

QJsonValue
Resume::getToken() const {
    return _jsonObject[TOKEN];
}

void
Resume::setToken(const QJsonValue &token) {
    _jsonObject[TOKEN] = token;
}

QJsonValue
Resume::getSessionId() const {
    return _jsonObject[SESSION_ID];
}

void
Resume::setSessionId(const QJsonValue &sessionId) {
    _jsonObject[SESSION_ID] = sessionId;
}

QJsonValue
Resume::getSeq() const {
    return _jsonObject[SEQ];
}

void
Resume::setSeq(const QJsonValue &seq) {
    _jsonObject[SEQ] = seq;
}
