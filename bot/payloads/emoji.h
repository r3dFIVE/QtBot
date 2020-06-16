#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializeable.h"

#include <QSharedPointer>


class Emoji : public JsonSerializeable
{
    const QString NAME = "name";
    const QString ID = "id";
    const QString ANIMATED = "animated";
public:
    QString name;
    QString id;
    QSharedPointer<bool> animated;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // EMOJI_H
