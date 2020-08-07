#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include "jsonserializable.h"


class Attachment : public JsonSerializable
{
    Q_OBJECT

public: 
    static const QString ID;
    static const QString FILENAME;
    static const QString SIZE;
    static const QString PROXY_URL;
    static const QString HEIGHT;
    static const QString WIDTH;
    static const QString URL;

    Attachment() {}
    Attachment(const QByteArray &json) : JsonSerializable(json) {}
    Attachment(const QJsonObject &json) : JsonSerializable(json) {}
    Attachment(const QString &json) : JsonSerializable(json) {}

    QJsonValue getFilename();
    QJsonValue getHeight();
    QJsonValue getId();
    QJsonValue getProxyUrl();
    QJsonValue getSize();
    QJsonValue getUrl();
    QJsonValue getWidth();
    void setFilename(QJsonValue filename);
    void setHeight(QJsonValue height);
    void setId(QJsonValue id);
    void setProxyUrl(QJsonValue proxy_url);
    void setSize(QJsonValue size);
    void setUrl(QJsonValue url);
    void setWidth(QJsonValue width);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue filename READ getFilename WRITE setFilename)
    Q_PROPERTY(QJsonValue size READ getSize WRITE setSize)
    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
};

Q_DECLARE_METATYPE(Attachment)

#endif // ATTACHMENT_H
