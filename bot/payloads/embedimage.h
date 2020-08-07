#ifndef EMBEDIMAGE_H
#define EMBEDIMAGE_H

#include "jsonserializable.h"


class EmbedImage : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString HEIGHT;
    static const QString PROXY_URL;
    static const QString URL;
    static const QString WIDTH;

    EmbedImage() {}
    EmbedImage(const QByteArray &json) : JsonSerializable(json) {}
    EmbedImage(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedImage(const QString &json) : JsonSerializable(json) {}

    QJsonValue getHeight() const;
    QJsonValue getProxyUrl() const;
    QJsonValue getUrl() const;
    QJsonValue getWidth() const;
    void setHeight(const QJsonValue &height);
    void setProxyUrl(const QJsonValue &proxyUrl);
    void setUrl(const QJsonValue &url);
    void setWidth(const QJsonValue &width);

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
};

Q_DECLARE_METATYPE(EmbedImage);

#endif // EMBEDIMAGE_H
