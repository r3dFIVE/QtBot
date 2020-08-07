#ifndef EMBEDVIDEO_H
#define EMBEDVIDEO_H

#include "jsonserializable.h"


class EmbedVideo : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString HEIGHT;
    static const QString URL;
    static const QString WIDTH;

    EmbedVideo() {}
    EmbedVideo(const QByteArray &json) : JsonSerializable(json) {}
    EmbedVideo(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedVideo(const QString &json) : JsonSerializable(json) {}

    void setHeight(const QJsonValue &height);
    void setUrl(const QJsonValue &url);
    void setWidth(const QJsonValue &width);
    QJsonValue getHeight() const;
    QJsonValue getUrl() const;
    QJsonValue getWidth() const;

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
};

Q_DECLARE_METATYPE(EmbedVideo)

#endif // EMBEDVIDEO_H
