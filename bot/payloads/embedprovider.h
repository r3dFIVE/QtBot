#ifndef EMBEDPROVIDER_H
#define EMBEDPROVIDER_H

#include "jsonserializable.h"

#include <QObject>

class EmbedProvider : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    QJsonValue url;

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    QJsonValue name;

    QJsonValue getUrl() const;
    void setUrl(const QJsonValue &value);
    QJsonValue getName() const;
    void setName(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    EmbedProvider() {}
    ~EmbedProvider() {}
};

Q_DECLARE_METATYPE(EmbedProvider)

#endif // EMBEDPROVIDER_H
