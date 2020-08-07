#ifndef EMBEDAUTHOR_H
#define EMBEDAUTHOR_H

#include "jsonserializable.h"


class EmbedAuthor : public JsonSerializable
{
    Q_OBJECT

public:
    const static QString ICON_URL;
    const static QString NAME;
    const static QString PROXY_ICON_URL;
    const static QString URL;

    EmbedAuthor() {}
    EmbedAuthor(const QByteArray &json) : JsonSerializable(json) {}
    EmbedAuthor(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedAuthor(const QString &json) : JsonSerializable(json) {}

    QJsonValue getIconUrl() const;
    QJsonValue getName() const;
    QJsonValue getProxyIconUrl() const;
    QJsonValue getUrl() const;
    void setIconUrl(const QJsonValue &iconUrl);
    void setName(const QJsonValue &name);
    void setProxyIconUrl(const QJsonValue &proxyIconUrl);
    void setUrl(const QJsonValue &url);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue icon_url READ getIconUrl WRITE setIconUrl)
    Q_PROPERTY(QJsonValue proxy_icon_url READ getProxyIconUrl WRITE setProxyIconUrl)
};

Q_DECLARE_METATYPE(EmbedAuthor)

#endif // EMBEDAUTHOR_H
