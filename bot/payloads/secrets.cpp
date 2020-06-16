#include "secrets.h"

void
Secrets::read(const QJsonObject &jsonObject) {
    if (jsonObject.contains(JOIN)) {
        join = jsonObject[JOIN].toString();
    }

    if (jsonObject.contains(SPECTATE)) {
        spectate = jsonObject[SPECTATE].toString();
    }

    if (jsonObject.contains(MATCH)) {
        match = jsonObject[MATCH].toString();
    }
}

void
Secrets::write(QJsonObject &jsonObject) const {
    if (!join.isEmpty()) {
        jsonObject[JOIN] = join;
    }

    if (!spectate.isEmpty()) {
        jsonObject[SPECTATE] = spectate;
    }

    if (!match.isEmpty()) {
        jsonObject[MATCH] = match;
    }
}
