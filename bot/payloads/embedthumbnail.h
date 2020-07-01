#ifndef EMBEDTHUMBNAIL_H
#define EMBEDTHUMBNAIL_H

#include "jsonserializable.h"

#include <QObject>


class EmbedThumbnail : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    QJsonValue url;

    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    QJsonValue proxy_url;

    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    QJsonValue height;

    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
    QJsonValue width;

    QJsonValue getUrl() const;
    void setUrl(const QJsonValue &value);
    QJsonValue getProxyUrl() const;
    void setProxyUrl(const QJsonValue &value);
    QJsonValue getHeight() const;
    void setHeight(const QJsonValue &value);
    QJsonValue getWidth() const;
    void setWidth(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    EmbedThumbnail() {}
    ~EmbedThumbnail() {}

};

Q_DECLARE_METATYPE(EmbedThumbnail)

#endif // EMBEDTHUMBNAIL_H
