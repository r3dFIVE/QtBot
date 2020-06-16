#ifndef ASSETS_H
#define ASSETS_H

#include "jsonserializeable.h"


class Assets : public JsonSerializeable
{
    const QString LARGE_IMAGE = "large_image";
    const QString LARGE_TEXT = "large_text";
    const QString SMALL_IMAGE = "small_image";
    const QString SMALL_TEXT = "small_text";
public:
    QString large_image;
    QString large_text;
    QString small_image;
    QString small_text;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};



#endif // ASSETS_H
