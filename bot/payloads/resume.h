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

    QString getToken();
    void setToken(QString token);
    QString getSessionId();
    void setSessionId(QString session_id);
    int getSeq();
    void setSeq(int seq);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(Resume)

#endif // RESUME_H
