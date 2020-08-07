#ifndef SECRETS_H
#define SECRETS_H

#include "jsonserializable.h"


class ActivitySecrets : public JsonSerializable
{
    Q_OBJECT

public:    
    static const QString JOIN;
    static const QString MATCH;
    static const QString SPECTATE;

    ActivitySecrets() {}
    ActivitySecrets(const QByteArray &json) : JsonSerializable(json) {}
    ActivitySecrets(const QJsonObject &json) : JsonSerializable(json) {}
    ActivitySecrets(const QString &json) : JsonSerializable(json) {}

    QJsonValue getJoin();
    QJsonValue getMatch();
    QJsonValue getSpectate();
    void setJoin(const QJsonValue &join);
    void setMatch(const QJsonValue &match);
    void setSpectate(const QJsonValue &spectate);

    Q_PROPERTY(QJsonValue join READ getJoin WRITE setJoin)
    Q_PROPERTY(QJsonValue spectate READ getSpectate WRITE setSpectate)
    Q_PROPERTY(QJsonValue match READ getMatch WRITE setMatch)
};

Q_DECLARE_METATYPE(ActivitySecrets)

#endif // SECRETS_H
