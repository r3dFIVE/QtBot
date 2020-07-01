#ifndef EMBEDVIDEO_H
#define EMBEDVIDEO_H

#include "jsonserializable.h"

#include <QObject>

class EmbedVideo : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    QJsonValue url;

    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    QJsonValue height;

    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
    QJsonValue width;

    QJsonValue getUrl() const;
    void setUrl(const QJsonValue &value);
    QJsonValue getHeight() const;
    void setHeight(const QJsonValue &value);
    QJsonValue getWidth() const;
    void setWidth(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    EmbedVideo() {}
    ~EmbedVideo() {}
};

Q_DECLARE_METATYPE(EmbedVideo)

#endif // EMBEDVIDEO_H
