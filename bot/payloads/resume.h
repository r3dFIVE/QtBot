#ifndef RESUME_H
#define RESUME_H

#include "jsonserializable.h"


class Resume : public JsonSerializable
{   
    Q_OBJECT

public:
    static const QString TOKEN;
    static const QString SESSION_ID;
    static const QString SEQ;

    Resume() {}
    Resume(const QByteArray &json) : JsonSerializable(json) {}
    Resume(const QJsonObject &json) : JsonSerializable(json) {}
    Resume(const QString &json) : JsonSerializable(json) {}

    QJsonValue getSeq()const;
    QJsonValue getSessionId() const;
    QJsonValue getToken() const;
    void setSeq(const QJsonValue &seq);
    void setSessionId(const QJsonValue &sessionId);
    void setToken(const QJsonValue &token);

    Q_PROPERTY(QJsonValue token READ getToken WRITE setToken)
    Q_PROPERTY(QJsonValue session_id READ getSessionId WRITE setSessionId)
    Q_PROPERTY(QJsonValue seq READ getSeq WRITE setSeq)
};

Q_DECLARE_METATYPE(Resume)

#endif // RESUME_H
