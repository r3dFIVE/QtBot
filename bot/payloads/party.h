#ifndef PARTY_H
#define PARTY_H

#include "jsonserializeable.h"

#include <QSharedPointer>


class Party : public JsonSerializeable
{
    const QString ID = "id";
    const QString SIZE = "size";
public:
    QString id;
    QSharedPointer<int> size[2];

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // PARTY_H
