#ifndef EMBEDPROVIDER_H
#define EMBEDPROVIDER_H

#include "jsonserializable.h"


class EmbedProvider : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString NAME;
    static const QString URL;

    EmbedProvider() {}
    EmbedProvider(const QByteArray &json) : JsonSerializable(json) {}
    EmbedProvider(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedProvider(const QString &json) : JsonSerializable(json) {}

    QJsonValue getName() const;
    QJsonValue getUrl() const;
    void setName(const QJsonValue &name);
    void setUrl(const QJsonValue &url);

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
};

Q_DECLARE_METATYPE(EmbedProvider)

#endif // EMBEDPROVIDER_H
