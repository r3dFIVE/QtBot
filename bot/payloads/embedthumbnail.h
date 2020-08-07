#ifndef EMBEDTHUMBNAIL_H
#define EMBEDTHUMBNAIL_H

#include "jsonserializable.h"


class EmbedThumbnail : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString HEIGHT;
    static const QString PROXY_URL;
    static const QString URL;
    static const QString WIDTH;

    EmbedThumbnail() {}
    EmbedThumbnail(const QByteArray &json) : JsonSerializable(json) {}
    EmbedThumbnail(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedThumbnail(const QString &json) : JsonSerializable(json) {}

    QJsonValue getHeight() const;
    QJsonValue getProxyUrl() const;
    QJsonValue getUrl() const;
    QJsonValue getWidth() const;
    void setHeight(const QJsonValue &height);
    void setProxyUrl(const QJsonValue &proxyUrl);
    void setWidth(const QJsonValue &width);
    void setUrl(const QJsonValue &url);

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
};

Q_DECLARE_METATYPE(EmbedThumbnail)

#endif // EMBEDTHUMBNAIL_H
