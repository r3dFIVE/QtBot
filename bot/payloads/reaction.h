#ifndef REACTION_H
#define REACTION_H

#include "jsonserializable.h"
#include "emoji.h"

#include <QObject>
#include <QSharedPointer>

class Reaction : public JsonSerializable
{
    Q_OBJECT
public:

    Q_PROPERTY(QJsonValue count READ getCount WRITE setCount)
    QJsonValue count;

    Q_PROPERTY(QJsonValue me READ getMe WRITE setMe)
    QJsonValue me;

    Q_PROPERTY(QJsonObject emoji READ getEmoji WRITE setEmoji)
    QSharedPointer<Emoji> emoji;

    QJsonValue getCount() const;
    void setCount(const QJsonValue &value);
    QJsonValue getMe() const;
    void setMe(const QJsonValue &value);
    QJsonObject getEmoji() const;
    void setEmoji(const QJsonObject &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    Reaction() {}
    ~Reaction() {}
};

Q_DECLARE_METATYPE(Reaction)

#endif // REACTION_H
