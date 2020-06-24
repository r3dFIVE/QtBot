#ifndef SECRETS_H
#define SECRETS_H

#include "jsonserializable.h"

class ActivitySecrets : public JsonSerializable
{
    Q_OBJECT
public:    
    const QString JOIN = "join";
    const QString SPECTATE = "spectate";
    const QString MATCH = "match";

    Q_PROPERTY(QString join READ getJoin WRITE setJoin)
    QString join;

    Q_PROPERTY(QString spectate READ getSpectate WRITE setSpectate)
    QString spectate;

    Q_PROPERTY(QString match READ getMatch WRITE setMatch)
    QString match;

    QString getJoin();
    void setJoin(QString join);
    QString getSpectate();
    void setSpectate(QString spectate);
    QString getMatch();
    void setMatch(QString match);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(ActivitySecrets)

#endif // SECRETS_H
