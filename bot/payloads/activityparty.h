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

    QString
    getId() {
        return id;
    }

    void
    setId(QString id) {
        this->id = id;
    }

    QJsonArray
    getSize() {
        if (size[0] && size[1]) {
            return QJsonArray { *size[0], *size[1] };
        } else {
            return QJsonArray();
        }
    }

    void
    setSize(QJsonArray size) {
        if (!size.isEmpty()) {
            this->size[0] = QSharedPointer<int>(new int(size[0].toInt()));
            this->size[1] = QSharedPointer<int>(new int(size[1].toInt()));
        }
    }

    void
    read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void
    write(QJsonObject &jsonObject) override  {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(ActivityParty)

#endif // PARTY_H
