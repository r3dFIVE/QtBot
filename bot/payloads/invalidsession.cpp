#include "invalidsession.h"


const QString InvalidSession::D = "d";
const QString InvalidSession::OP = "op";

QJsonValue
InvalidSession::getD() const {
    return _jsonObject[D];
}

QJsonValue
InvalidSession::getOP() const {
    return _jsonObject[OP];
}

void
InvalidSession::setD(const QJsonValue &d) {
    _jsonObject[D] = d;
}

void
InvalidSession::setOP(const QJsonValue &op) {
    _jsonObject[OP] = op;
}
