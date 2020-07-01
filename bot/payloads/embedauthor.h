#ifndef EMBEDAUTHOR_H
#define EMBEDAUTHOR_H

#include "jsonserializable.h"

#include <QObject>

class EmbedAuthor : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    QJsonValue name;

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    QJsonValue url;

    Q_PROPERTY(QJsonValue icon_url READ getIconUrl WRITE setIconUrl)
    QJsonValue icon_url;

    Q_PROPERTY(QJsonValue proxy_icon_url READ getProxyIconUrl WRITE setProxyIconUrl)
    QJsonValue proxy_icon_url;


    QJsonValue getName() const;
    void setName(const QJsonValue &value);
    QJsonValue getUrl() const;
    void setUrl(const QJsonValue &value);
    QJsonValue getIconUrl() const;
    void setIconUrl(const QJsonValue &value);
    QJsonValue getProxyIconUrl() const;
    void setProxyIconUrl(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    EmbedAuthor() {}
    ~EmbedAuthor() {}
};

Q_DECLARE_METATYPE(EmbedAuthor)

#endif // EMBEDAUTHOR_H
