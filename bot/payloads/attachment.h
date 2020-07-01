#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include "jsonserializable.h"

#include <QObject>

class Attachment : public JsonSerializable
{
    Q_OBJECT

public:
    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    QJsonValue id;

    Q_PROPERTY(QJsonValue filename READ getFilename WRITE setFilename)
    QJsonValue filename;

    Q_PROPERTY(QJsonValue size READ getSize WRITE setSize)
    QJsonValue size;

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    QJsonValue url;

    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    QJsonValue proxy_url;

    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    QJsonValue height;

    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
    QJsonValue width;

    QJsonValue getId();
    void setId(QJsonValue id);
    QJsonValue getFilename();
    void setFilename(QJsonValue filename);
    QJsonValue getSize();
    void setSize(QJsonValue size);
    QJsonValue getUrl();
    void setUrl(QJsonValue url);
    QJsonValue getProxyUrl();
    void setProxyUrl(QJsonValue proxy_url);
    QJsonValue getHeight();
    void setHeight(QJsonValue height);
    QJsonValue getWidth();
    void setWidth(QJsonValue width);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    Attachment() {}
    ~Attachment() {}
};

Q_DECLARE_METATYPE(Attachment)

#endif // ATTACHMENT_H
