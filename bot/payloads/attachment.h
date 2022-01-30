/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include "jsonserializable.h"


class Attachment : public JsonSerializable
{
    Q_OBJECT

public: 
    static const QString DESCRIPTION;
    static const QString CONTENT_TYPE;
    static const QString CHECKSUM;
    static const QString ID;
    static const QString FILENAME;
    static const QString SIZE;
    static const QString PROXY_URL;
    static const QString HEIGHT;
    static const QString WIDTH;
    static const QString URL;    
    static const QString MESSAGE_ID;
    static const QString USER_ID;
    static const QString CHANNEL_ID;
    static const QString GUILD_ID;

    Attachment() {}
    Attachment(const QByteArray &json) : JsonSerializable(json) {}
    Attachment(const QJsonObject &json) : JsonSerializable(json) {}
    Attachment(const QString &json) : JsonSerializable(json) {}
    Attachment(const Attachment &other) {
        if (this == &other) {
            return;
        }

        _jsonObject = other._jsonObject;
    }

    Attachment operator=(const Attachment &other) {
        if (this == &other) {
            return *this;
        }

        _jsonObject = other._jsonObject;

        return *this;
    }

    QJsonValue getDescription() const;
    QJsonValue getContentType() const;
    QJsonValue getChecksum() const;
    QJsonValue getFilename() const;
    QJsonValue getHeight() const;
    QJsonValue getId() const;
    QJsonValue getProxyUrl() const;
    QJsonValue getSize() const;
    QJsonValue getUrl() const;
    QJsonValue getWidth() const;
    QJsonValue getMessageId() const;
    QJsonValue getUserId() const;
    QJsonValue getGuildId() const;
    QJsonValue getChannelId() const;
    void setDescription(const QJsonValue &description);
    void setContentType(const QJsonValue &contentType);
    void setChecksum(const QJsonValue &checksum);
    void setFilename(const QJsonValue &filename);
    void setHeight(const QJsonValue &height);
    void setId(const QJsonValue &id);
    void setProxyUrl(const QJsonValue &proxy_url);
    void setSize(const QJsonValue &size);
    void setUrl(const QJsonValue &url);
    void setWidth(const QJsonValue &width);
    void setMessageId(const QJsonValue &messageId);
    void setUserId(const QJsonValue &userId);
    void setGuildId(const QJsonValue &guildId);
    void setChannelId(const QJsonValue &channelId);

    Q_PROPERTY(QJsonValue checksum READ getChecksum WRITE setChecksum)
    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue filename READ getFilename WRITE setFilename)
    Q_PROPERTY(QJsonValue size READ getSize WRITE setSize)
    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
    Q_PROPERTY(QJsonValue messageId READ getMessageId WRITE setMessageId)
    Q_PROPERTY(QJsonValue userId READ getUserId WRITE setUserId)
    Q_PROPERTY(QJsonValue guildId READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue channelId READ getChannelId WRITE setChannelId)
};

Q_DECLARE_METATYPE(Attachment)

#endif // ATTACHMENT_H
