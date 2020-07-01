#ifndef EMBEDFOOTER_H
#define EMBEDFOOTER_H

#include "jsonserializable.h"

#include <QObject>

class EmbedFooter : public JsonSerializable
{
    Q_OBJECT

public:
    Q_PROPERTY(QJsonValue text READ getText WRITE setText)
    QJsonValue text;

    Q_PROPERTY(QJsonValue icon_url READ getIconUrl WRITE setIconUrl)
    QJsonValue icon_url;

    Q_PROPERTY(QJsonValue proxy_icon_url READ getProxyIconUrl WRITE setProxyIconUrl)
    QJsonValue proxy_icon_url;

    QJsonValue getText() const;
    void setText(const QJsonValue &value);
    QJsonValue getIconUrl() const;
    void setIconUrl(const QJsonValue &value);
    QJsonValue getProxyIconUrl() const;
    void setProxyIconUrl(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    EmbedFooter() {}
    ~EmbedFooter() {}
};

Q_DECLARE_METATYPE(EmbedFooter)

#endif // EMBEDFOOTER_H
