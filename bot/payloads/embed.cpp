#include "embed.h"

#include <util/jsonutils.h>


QJsonValue
Embed::getTitle() const {
    return title;
}

void
Embed::setTitle(const QJsonValue &value) {
    title = value;
}

QJsonValue
Embed::getType() const {
    return type;
}

void
Embed::setType(const QJsonValue &value) {
    type = value;
}

QJsonValue
Embed::getDescription() const {
    return description;
}

void
Embed::setDescription(const QJsonValue &value) {
    description = value;
}

QJsonValue
Embed::getUrl() const {
    return url;
}

void
Embed::setUrl(const QJsonValue &value) {
    url = value;
}

QJsonValue
Embed::getTimestamp() const {
    return timestamp;
}

void
Embed::setTimestamp(const QJsonValue &value) {
    timestamp = value;
}

QJsonValue
Embed::getColor() const {
    return color;
}

void
Embed::setColor(const QJsonValue &value) {
    color = value;
}

QJsonObject
Embed::getFooter() const {
    if (footer) {
        return footer->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Embed::setFooter(const QJsonObject &value) {
    if (!value.isEmpty()) {
        footer = QSharedPointer<EmbedFooter>(new EmbedFooter);
        footer->fromQJsonObject(value);
    }
}

QJsonObject
Embed::getImage() const {
    if (image) {
        return image->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Embed::setImage(const QJsonObject &value) {
    if (!value.isEmpty()) {
        image = QSharedPointer<EmbedImage>(new EmbedImage);
        image->fromQJsonObject(value);
    }
}

QJsonObject
Embed::getThumbnail() const {
    if (thumbnail) {
        return thumbnail->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Embed::setThumbnail(const QJsonObject &value) {
    if (!value.isEmpty()) {
        thumbnail = QSharedPointer<EmbedThumbnail>(new EmbedThumbnail);
        thumbnail->fromQJsonObject(value);
    }
}

QJsonObject
Embed::getVideo() const {
    if (video) {
        return video->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Embed::setVideo(const QJsonObject &value) {
    if (!value.isEmpty()) {
        video = QSharedPointer<EmbedVideo>(new EmbedVideo);
        video->fromQJsonObject(value);
    }
}

QJsonObject
Embed::getProvider() const {
    if (provider) {
        return provider->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Embed::setProvider(const QJsonObject &value) {
    if (!value.isEmpty()) {
        provider = QSharedPointer<EmbedProvider>(new EmbedProvider);
        provider->fromQJsonObject(value);
    }
}

QJsonObject
Embed::getAuthor() const {
    if (author) {
        return author->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Embed::setAuthor(const QJsonObject &value) {
    if (!value.isEmpty()) {
        author = QSharedPointer<EmbedAuthor>(new EmbedAuthor);
        author->fromQJsonObject(value);
    }
}


QJsonArray
Embed::getFields() const {
    QJsonArray fields;
    for (QSharedPointer<EmbedField> field : this->fields) {
        if (field) {
            fields.push_back(field->toQJsonObject());
        }
    }
    return fields;
}

void
Embed::setFields(const QJsonArray &values) {
    for (QJsonValue value : values) {
        if (!value.isNull()) {
            QSharedPointer<EmbedField> field = QSharedPointer<EmbedField>(new EmbedField);
            JsonUtils::readFromJson(*field, value.toObject());
            fields.push_back(field);
        }
    }
}

void
Embed::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
Embed::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}

