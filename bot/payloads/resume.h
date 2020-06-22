#ifndef RESUME_H
#define RESUME_H

#include "jsonserializable.h"


class Resume : public JsonSerializable
{   
    Q_OBJECT
public:
    const QString TOKEN = "token";
    const QString SESSION_ID = "session_id";
    const QString SEQ = "seq";

    Q_PROPERTY(QString token READ getToken WRITE setToken)
    QString token;

    Q_PROPERTY(QString session_id READ getSessionId WRITE setSessionId)
    QString session_id;

    Q_PROPERTY(int seq READ getSeq WRITE setSeq)
    int seq;

    QString
    getToken() {
        return token;
    }

    void
    setToken(QString token) {
        this->token = token;
    }

    QString
    getSessionId() {
        return session_id;
    }

    void
    setSessionId(QString session_id) {
        this->session_id = session_id;
    }

    int
    getSeq() {
        return seq;
    }

    void
    setSeq(int seq) {
        this->seq = seq;
    }

    void
    read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void
    write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(Resume)

#endif // RESUME_H
