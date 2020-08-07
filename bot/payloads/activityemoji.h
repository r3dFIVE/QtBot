#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializable.h"


class ActivityEmoji : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString NAME;
    static const QString ID;
    static const QString ANIMATED;

    ActivityEmoji() {}
    ActivityEmoji(const QByteArray &json) : JsonSerializable(json) {}
    ActivityEmoji(const QJsonObject &json) : JsonSerializable(json) {}
    ActivityEmoji(const QString &json) : JsonSerializable(json) {}

    QJsonValue getAnimated() const;
    QJsonValue getId() const;
    QJsonValue getName() const;
    void setAnimated(const QJsonValue &animated);
    void setId(const QJsonValue &id);
    void setName(const QJsonValue &name);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue animated READ getAnimated WRITE setAnimated)
};

Q_DECLARE_METATYPE(ActivityEmoji)

#endif // EMOJI_H
