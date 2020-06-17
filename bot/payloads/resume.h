#ifndef RESUME_H
#define RESUME_H

#include "jsonserializeable.h"


class Resume : public JsonSerializeable
{   
public:
    const QString TOKEN = "token";
    const QString SESSION_ID = "session_id";
    const QString SEQ = "seq";

    QString token;
    QString session_id;
    int seq;

    void read(const QJsonObject &jsonObject) override {
        token = jsonObject[TOKEN].toString();
        session_id = jsonObject[SESSION_ID].toString();
        seq = jsonObject[SEQ].toInt();
    }

    void write(QJsonObject &jsonObject) const override {
        jsonObject[TOKEN] = token;
        jsonObject[SESSION_ID] = session_id;
        jsonObject[SEQ] = seq;
    }
};

#endif // RESUME_H
