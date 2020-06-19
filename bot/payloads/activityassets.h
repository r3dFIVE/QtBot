#ifndef ASSETS_H
#define ASSETS_H

#include "jsonserializeable.h"


class ActivityAssets : public JsonSerializeable
{
    Q_OBJECT
public:
    const QString LARGE_IMAGE = "large_image";
    const QString LARGE_TEXT = "large_text";
    const QString SMALL_IMAGE = "small_image";
    const QString SMALL_TEXT = "small_text";

    Q_PROPERTY(QString large_image READ getLargeImage WRITE setLargeImage)
    QString large_image;

    Q_PROPERTY(QString large_text READ getLargeText WRITE setLargeText)
    QString large_text;

    Q_PROPERTY(QString small_image READ getSmallImage WRITE setSmallImage)
    QString small_image;

    Q_PROPERTY(QString small_text READ getSmallText WRITE setSmallText)
    QString small_text;

    QString getLargeText() const {
        return large_text;
    }

    void setLargeText(const QString &value) {
        large_text = value;
    }
    QString getSmallImage() const {
        return small_image;
    }

    void setSmallImage(const QString &value) {
        small_image = value;
    }

    QString getSmallText() const {
        return small_text;
    }

    void setSmallText(const QString &value) {
        small_text = value;
    }

    QString getLargeImage() const {
        return large_image;
    }

    void setLargeImage(const QString &value) {
        large_image = value;
    }

    void
    read(const QJsonObject &jsonObject) override  {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void
    write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(ActivityAssets)

#endif // ASSETS_H


