#ifndef EMBEDFOOTER_H
#define EMBEDFOOTER_H

#include "jsonserializable.h"


class EmbedFooter : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ICON_URL;
    static const QString PROXY_ICON_URL;
    static const QString TEXT;



    QJsonValue getIconUrl() const;
    QJsonValue getProxyIconUrl() const;
    QJsonValue getText() const;
    void setIconUrl(const QJsonValue &value);
    void setProxyIconUrl(const QJsonValue &value);
    void setText(const QJsonValue &value);

    Q_PROPERTY(QJsonValue text READ getText WRITE setText)
    Q_PROPERTY(QJsonValue icon_url READ getIconUrl WRITE setIconUrl)
    Q_PROPERTY(QJsonValue proxy_icon_url READ getProxyIconUrl WRITE setProxyIconUrl)
};

Q_DECLARE_METATYPE(EmbedFooter)

#endif // EMBEDFOOTER_H
