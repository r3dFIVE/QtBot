#ifndef SECRETS_H
#define SECRETS_H

#include "jsonserializeable.h"

class Secrets : public JsonSerializeable
{
    const QString JOIN = "join";
    const QString SPECTATE = "spectate";
    const QString MATCH = "match";
public:    
    QString join;
    QString spectate;
    QString match;

    void read(const QJsonObject &jsonObject) override {
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

    void write(QJsonObject &jsonObject) const override {
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
};

#endif // SECRETS_H
