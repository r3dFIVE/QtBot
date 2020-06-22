#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializable.h"

#include <QSharedPointer>


class ActivityEmoji : public JsonSerializable
{
    Q_OBJECT
public:
    const QString NAME = "name";
    const QString ID = "id";
    const QString ANIMATED = "animated";

    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QJsonValue animated READ getAnimated WRITE setAnimated)
    QSharedPointer<bool> animated;

    QString
    getName() {
        return name;
    }

    void
    setName(QString name) {
        this->name = name;
    }

    QString
    getId() {
        return id;
    }

    void
    setId(QString id) {
        this->id = id;
    }

    QJsonValue
    getAnimated() {
        if (animated) {
            return QJsonValue(*animated);
        }
        return QJsonValue();
    }

    void
    setAnimated(QJsonValue animated) {
        if (!animated.isNull()) {
            this->animated = QSharedPointer<bool>(new bool(animated.toBool()));
        }
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

Q_DECLARE_METATYPE(ActivityEmoji)

#endif // EMOJI_H
