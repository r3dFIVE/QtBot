#ifndef GUILD_H
#define GUILD_H

#include "jsonserializable.h"


class Guild : public JsonSerializable
{
    Q_OBJECT

public:

    void read(const QJsonObject &jsonObject) override {}
    void write(QJsonObject &jsonObject) override {}

//    const QString ID
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
//    const QString
};

Q_DECLARE_METATYPE(Guild)

#endif // GUILD_H
