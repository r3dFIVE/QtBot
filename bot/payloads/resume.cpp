#include "resume.h"

void
Resume::read(const QJsonObject &jsonObject) {
    token = jsonObject[TOKEN].toString();
    session_id = jsonObject[SESSION_ID].toString();
    seq = jsonObject[SEQ].toInt();
}

void
Resume::write(QJsonObject &jsonObject) const {
    jsonObject[TOKEN] = token;
    jsonObject[SESSION_ID] = session_id;
    jsonObject[SEQ] = seq;
}
