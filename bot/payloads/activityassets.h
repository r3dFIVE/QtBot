#ifndef ASSETS_H
#define ASSETS_H

#include "jsonserializable.h"


class ActivityAssets : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString LARGE_IMAGE;
    static const QString LARGE_TEXT;
    static const QString SMALL_IMAGE;
    static const QString SMALL_TEXT;

    ActivityAssets() {}
    ActivityAssets(const QByteArray &json) : JsonSerializable(json) {}
    ActivityAssets(const QJsonObject &json) : JsonSerializable(json) {}
    ActivityAssets(const QString &json) : JsonSerializable(json) {}

    QJsonValue getLargeText();
    QJsonValue getSmallImage();
    QJsonValue getSmallText();
    QJsonValue getLargeImage();
    void setLargeImage(const QJsonValue &largeImage);
    void setLargeText(const QJsonValue &largeText);
    void setSmallImage(const QJsonValue &smallImage);
    void setSmallText(const QJsonValue &smallText);

    Q_PROPERTY(QJsonValue large_image READ getLargeImage WRITE setLargeImage)
    Q_PROPERTY(QJsonValue large_text READ getLargeText WRITE setLargeText)
    Q_PROPERTY(QJsonValue small_image READ getSmallImage WRITE setSmallImage)
    Q_PROPERTY(QJsonValue small_text READ getSmallText WRITE setSmallText)
};

Q_DECLARE_METATYPE(ActivityAssets)

#endif // ASSETS_H


