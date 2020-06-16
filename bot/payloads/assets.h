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

    void read(const QJsonObject &jsonObject) override  {
        large_image = jsonObject[LARGE_IMAGE].toString();
        large_text = jsonObject[LARGE_TEXT].toString();
        small_image = jsonObject[SMALL_IMAGE].toString();
        small_text = jsonObject[SMALL_TEXT].toString();
    }

    void write(QJsonObject &jsonObject) const override {
        if (!large_image.isEmpty()) {
            jsonObject[LARGE_IMAGE] = large_image;
        }

        if (!large_text.isEmpty()) {
            jsonObject[LARGE_TEXT] = large_text;
        }

        if (!small_image.isEmpty()) {
            jsonObject[SMALL_IMAGE] = small_image;
        }

        if (!small_text.isEmpty()) {
            jsonObject[SMALL_TEXT] = small_text;
        }
    }

};

#endif // ASSETS_H
