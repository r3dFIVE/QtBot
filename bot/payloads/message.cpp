#include "message.h"

#include "util/serializationutils.h"


QJsonValue
Message::getId() const {
    return id;
}

void
Message::setId(const QJsonValue &value) {
    id = value;
}

QJsonValue
Message::getChannelId() const {
    return channel_id;
}

void
Message::setChannelId(const QJsonValue &value) {
    channel_id = value;
}

QJsonValue
Message::getGuildId() const {
    return guild_id;
}

void
Message::setGuildId(const QJsonValue &value) {
    guild_id = value;
}

QJsonObject
Message::getAuthor() const {
    if (author) {
        return author->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Message::setAuthor(const QJsonObject &value) {
    if (!value.isEmpty()) {
        author = QSharedPointer<User>(new User);
        SerializationUtils::readFromJson(*author, value);
    }
}

QJsonObject
Message::getMember() const {
    if (member) {
        return member->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Message::setMember(const QJsonObject &value) {
    if (!value.isEmpty()) {
        member = QSharedPointer<GuildMember>(new GuildMember);
        SerializationUtils::readFromJson(*member, value);
    }
}

QJsonValue
Message::getContent() const {
    return content;
}

void
Message::setContent(const QJsonValue &value) {
    content = value;
}

QJsonValue
Message::getTimestamp() const {
    return timestamp;
}

void
Message::setTimestamp(const QJsonValue &value) {
    timestamp = value;
}

QJsonValue
Message::getEditedTimestamp() const {
    return edited_timestamp;
}

void
Message::setEditedTimestamp(const QJsonValue &value) {
    edited_timestamp = value;
}

QJsonValue
Message::getTts() const {
    return tts;
}

void
Message::setTts(const QJsonValue &value) {
    tts = value;
}

QJsonValue
Message::getMentionEveryone() const {
    return mention_everyone;
}

void
Message::setMentionEveryone(const QJsonValue &value) {
    mention_everyone = value;
}

QJsonArray
Message::getMentions() const {
    QJsonArray mentions;
    for (QSharedPointer<User> mention : this->mentions) {
        if (mention) {
            mentions.push_back(mention->toQJsonObject());
        }
    }
    return mentions;
}

void
Message::setMentions(const QJsonArray &values) {
    for (QJsonValue value : values) {
        if (!value.isNull()) {
            QSharedPointer<User> mention = QSharedPointer<User>(new User);
            SerializationUtils::readFromJson(*mention, value.toObject());
            mentions.push_back(mention);
        }
    }
}

QJsonArray
Message::getMentionRoles() const {
    QJsonArray mention_roles;
    for (QString roleId : this->mention_roles) {
        mention_roles.push_back(roleId);
    }
    return mention_roles;
}

void
Message::setMentionRoles(const QJsonArray &values) {
    for (QJsonValue value : values) {
        mention_roles.push_back(value.toString());
    }
}

QJsonArray
Message::getMentionChannels() const {
    QJsonArray mention_channels;
    for (QSharedPointer<ChannelMention> channel : this->mention_channels) {
        if (channel) {
            mention_channels.push_back(channel->toQJsonObject());
        }
    }
    return mention_channels;
}

void
Message::setMentionChannels(const QJsonArray &values) {
    for (QJsonValue value : values) {
        if (!value.isNull()) {
            QSharedPointer<ChannelMention> channel = QSharedPointer<ChannelMention>(new ChannelMention);
            SerializationUtils::readFromJson(*channel, value.toObject());
            mention_channels.push_back(channel);
        }
    }
}

QJsonArray
Message::getAttachments() const {
    QJsonArray attachments;
    for (QSharedPointer<Attachment> attachment : this->attachments) {
        if (attachment) {
            attachments.push_back(attachment->toQJsonObject());
        }
    }
    return attachments;
}

void
Message::setAttachments(const QJsonArray &values) {
    for (QJsonValue value : values) {
        if (!value.isNull()) {
            QSharedPointer<Attachment> attachment = QSharedPointer<Attachment>(new Attachment);
            SerializationUtils::readFromJson(*attachment, value.toObject());
            attachments.push_back(attachment);
        }
    }
}

QJsonArray
Message::getEmbeds() const {
    QJsonArray embeds;
    for (QSharedPointer<Embed> embed : this->embeds) {
        if (embed) {
            embeds.push_back(embed->toQJsonObject());
        }
    }
    return embeds;
}

void
Message::setEmbeds(const QJsonArray &values) {
    for (QJsonValue value : values) {
        if (!value.isNull()) {
            QSharedPointer<Embed> embed = QSharedPointer<Embed>(new Embed);
            SerializationUtils::readFromJson(*embed, value.toObject());
            embeds.push_back(embed);
        }
    }
}

QJsonArray
Message::getReactions() const {
    QJsonArray reactions;
    for (QSharedPointer<Reaction> reaction : this->reactions) {
        if (reaction) {
            reactions.push_back(reaction->toQJsonObject());
        }
    }
    return reactions;
}

void
Message::setReactions(const QJsonArray &values) {
    for (QJsonValue value : values) {
        if (!value.isNull()) {
            QSharedPointer<Reaction> reaction = QSharedPointer<Reaction>(new Reaction);
            SerializationUtils::readFromJson(*reaction, value.toObject());
            reactions.push_back(reaction);
        }
    }
}

QJsonValue
Message::getNonce() const {
    return nonce;
}

void
Message::setNonce(const QJsonValue &value) {
    nonce = value;
}

QJsonValue
Message::getPinned() const {
    return pinned;
}

void
Message::setPinned(const QJsonValue &value) {
    pinned = value;
}

QJsonValue
Message::getWebhookId() const {
    return webhook_id;
}

void
Message::setWebhookId(const QJsonValue &value) {
    webhook_id = value;
}

QJsonValue
Message::getType() const {
    return type;
}

void
Message::setType(const QJsonValue &value) {
    type = value;
}

QJsonObject
Message::getActivity() const {
    if (activity) {
        return activity->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Message::setActivity(const QJsonObject &value) {
    if (!value.isEmpty()) {
        activity = QSharedPointer<MessageActivity>(new MessageActivity);
        SerializationUtils::readFromJson(*activity, value);
    }
}

QJsonObject
Message::getApplication() const {
    if (application) {
        return application->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Message::setApplication(const QJsonObject &value) {
    if (!value.isEmpty()) {
        application = QSharedPointer<MessageApplication>(new MessageApplication);
        SerializationUtils::readFromJson(*application, value);
    }
}

QJsonObject
Message::getMessageReference() const {
    if (message_reference) {
        return message_reference->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Message::setMessageReference(const QJsonObject &value) {
    if (!value.isEmpty()) {
        message_reference = QSharedPointer<MessageReference>(new MessageReference);
        SerializationUtils::readFromJson(*message_reference, value);
    }
}

QJsonValue
Message::getFlags() const {
    return flags;
}

void
Message::setFlags(const QJsonValue &value) {
    flags = value;
}

void
Message::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
Message::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
