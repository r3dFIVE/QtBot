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

    QString
    getJoin() {
        return join;
    }

    void
    setJoin(QString join) {
        this->join = join;
    }

    QString
    getSpectate() {
        return spectate;
    }

    void
    setSpectate(QString spectate) {
        this->spectate = spectate;
    }

    QString
    getMatch() {
        return match;
    }

    void
    setMatch(QString match) {
        this->match = match;
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

Q_DECLARE_METATYPE(ActivitySecrets)

#endif // SECRETS_H
