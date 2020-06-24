#ifndef PARTY_H
#define PARTY_H

#include "jsonserializable.h"

#include <QSharedPointer>
#include <QJsonArray>

class ActivityParty : public JsonSerializable
{
    Q_OBJECT
public:
    const QString ID = "id";
    const QString SIZE = "size";

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QJsonArray size READ getSize WRITE setSize)
    QSharedPointer<int> size[2];

    QString getId();
    void setId(QString id);
    QJsonArray getSize();
    void setSize(QJsonArray size);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(ActivityParty)

#endif // PARTY_H
