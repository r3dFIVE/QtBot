#ifndef ASSETS_H
#define ASSETS_H

#include "jsonserializable.h"

class ActivityAssets : public JsonSerializable
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

    QString getLargeText();
    void setLargeText(QString &value);
    QString getSmallImage();
    void setSmallImage(QString &value);
    QString getSmallText();
    void setSmallText(QString &value);
    QString getLargeImage();
    void setLargeImage(QString &value);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(ActivityAssets)

#endif // ASSETS_H


