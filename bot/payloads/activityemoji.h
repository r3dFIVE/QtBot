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

    QString getName();
    void setName(QString name);
    QString getId();
    void setId(QString id);
    QJsonValue getAnimated();
    void setAnimated(QJsonValue animated);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(ActivityEmoji)

#endif // EMOJI_H
