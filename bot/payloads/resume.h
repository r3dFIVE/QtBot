#ifndef RESUME_H
#define RESUME_H

#include "jsonserializeable.h"


class Resume : public JsonSerializeable
{   
    const QString TOKEN = "token";
    const QString SESSION_ID = "session_id";
    const QString SEQ = "seq";
public:
    QString token;
    QString session_id;
    int seq;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // RESUME_H
