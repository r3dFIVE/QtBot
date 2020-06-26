#include "invalidsession.h"

void
InvalidSession::read(const QJsonObject &jsonObject) {
    op = jsonObject[OP].toInt();
    d = jsonObject[D].toBool();
}

void
InvalidSession::write(QJsonObject &jsonObject) {
    jsonObject[OP] = op;
    jsonObject[D] = d;
}
