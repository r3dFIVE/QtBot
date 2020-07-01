#ifndef EMBED_H
#define EMBED_H

#include "jsonserializable.h"
#include "embedfooter.h"
#include "embedimage.h"
#include "embedthumbnail.h"
#include "embedvideo.h"
#include "embedprovider.h"
#include "embedauthor.h"
#include "embedfield.h"

#include <QObject>
#include <QSharedPointer>

class Embed : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue title READ getTitle WRITE setTitle)
    QJsonValue title;

    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    QJsonValue type;

    Q_PROPERTY(QJsonValue description READ getDescription WRITE setDescription)
    QJsonValue description;

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    QJsonValue url;

    Q_PROPERTY(QJsonValue timestamp READ getTimestamp WRITE setTimestamp)
    QJsonValue timestamp;

    Q_PROPERTY(QJsonValue color READ getColor WRITE setColor)
    QJsonValue color;

    Q_PROPERTY(QJsonObject footer READ getFooter WRITE setFooter)
    QSharedPointer<EmbedFooter> footer;

    Q_PROPERTY(QJsonObject image READ getImage WRITE setImage)
    QSharedPointer<EmbedImage> image;

    Q_PROPERTY(QJsonObject thumbnail READ getThumbnail WRITE setThumbnail)
    QSharedPointer<EmbedThumbnail> thumbnail;

    Q_PROPERTY(QJsonObject video READ getVideo WRITE setVideo)
    QSharedPointer<EmbedVideo> video;

    Q_PROPERTY(QJsonObject provider READ getProvider WRITE setProvider)
    QSharedPointer<EmbedProvider> provider;

    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    QSharedPointer<EmbedAuthor> author;

    Q_PROPERTY(QJsonArray fields READ getFields WRITE setFields)
    QList<QSharedPointer<EmbedField>> fields;


    QJsonValue getTitle() const;
    void setTitle(const QJsonValue &value);
    QJsonValue getType() const;
    void setType(const QJsonValue &value);
    QJsonValue getDescription() const;
    void setDescription(const QJsonValue &value);
    QJsonValue getUrl() const;
    void setUrl(const QJsonValue &value);
    QJsonValue getTimestamp() const;
    void setTimestamp(const QJsonValue &value);
    QJsonValue getColor() const;
    void setColor(const QJsonValue &value);
    QJsonObject getFooter() const;
    void setFooter(const QJsonObject &value);
    QJsonObject getImage() const;
    void setImage(const QJsonObject &value);
    QJsonObject getThumbnail() const;
    void setThumbnail(const QJsonObject &value);
    QJsonObject getVideo() const;
    void setVideo(const QJsonObject &value);
    QJsonObject getProvider() const;
    void setProvider(const QJsonObject &value);
    QJsonObject getAuthor() const;
    void setAuthor(const QJsonObject &value);
    QJsonArray getFields() const;
    void setFields(const QJsonArray &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    Embed() {}
    ~Embed() {}
};

Q_DECLARE_METATYPE(Embed)

#endif // EMBED_H
