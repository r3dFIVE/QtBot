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

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // SECRETS_H
