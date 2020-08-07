#ifndef REACTION_H
#define REACTION_H

#include "jsonserializable.h"


class Reaction : public JsonSerializable
{
    Q_OBJECT
public:
    static const QString EMOJI;
    static const QString COUNT;
    static const QString ME;

    Reaction() {}
    Reaction(const QByteArray &json) : JsonSerializable(json) {}
    Reaction(const QJsonObject &json) : JsonSerializable(json) {}
    Reaction(const QString &json) : JsonSerializable(json) {}

    QJsonObject getEmoji() const;
    QJsonValue getCount() const;
    QJsonValue getMe() const;
    void setCount(const QJsonValue &count);
    void setEmoji(const QJsonObject &emoji);
    void setMe(const QJsonValue &me);

    Q_PROPERTY(QJsonValue count READ getCount WRITE setCount)
    Q_PROPERTY(QJsonValue me READ getMe WRITE setMe)
    Q_PROPERTY(QJsonObject emoji READ getEmoji WRITE setEmoji)
};

Q_DECLARE_METATYPE(Reaction)

#endif // REACTION_H
