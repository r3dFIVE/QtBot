#ifndef MESSAGE_H
#define MESSAGE_H

#include "jsonserializable.h"


class Message : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString CHANNEL_ID;
    static const QString GUILD_ID;
    static const QString AUTHOR;
    static const QString MEMBER;
    static const QString CONTENT;
    static const QString TIMESTAMP;
    static const QString EDITED_TIMESTAMP;
    static const QString TTS;
    static const QString MENTION_EVERYONE;
    static const QString MENTIONS;
    static const QString MENTION_ROLES;
    static const QString MENTION_CHANNELS;
    static const QString ATTACHMENTS;
    static const QString EMBEDS;
    static const QString REACTIONS;
    static const QString NONCE;
    static const QString PINNED;
    static const QString WEBHOOK_ID;
    static const QString TYPE;
    static const QString ACTIVITY;
    static const QString APPLICATION;
    static const QString MESSAGE_REFERENCE;
    static const QString FLAGS;

    Message() {}
    Message(const QByteArray &json) : JsonSerializable(json) {}
    Message(const QJsonObject &json) : JsonSerializable(json) {}
    Message(const QString &json) : JsonSerializable(json) {}

    QJsonArray getAttachments() const;
    QJsonArray getEmbeds() const;
    QJsonArray getMentionChannels() const;
    QJsonArray getMentionRoles() const;
    QJsonArray getMentions() const;
    QJsonArray getReactions() const;
    QJsonObject getActivity() const;
    QJsonObject getApplication() const;
    QJsonObject getAuthor() const;
    QJsonObject getMember() const;
    QJsonObject getMessageReference() const;
    QJsonValue getChannelId() const;
    QJsonValue getContent() const;
    QJsonValue getEditedTimestamp() const;
    QJsonValue getFlags() const;
    QJsonValue getGuildId() const;
    QJsonValue getId() const;
    QJsonValue getMentionEveryone() const;
    QJsonValue getNonce() const;
    QJsonValue getPinned() const;
    QJsonValue getTimestamp() const;
    QJsonValue getTTS() const;
    QJsonValue getType() const;
    QJsonValue getWebhookId() const;

    void setActivity(const QJsonObject &activity);
    void setApplication(const QJsonObject &application);
    void setAttachments(const QJsonArray &attachments);
    void setAuthor(const QJsonObject &author);
    void setChannelId(const QJsonValue &channel_id);
    void setContent(const QJsonValue &content);
    void setEditedTimestamp(const QJsonValue &value);
    void setEmbeds(const QJsonArray &embeds);
    void setFlags(const QJsonValue &value);
    void setGuildId(const QJsonValue &guildId);
    void setId(const QJsonValue &id);
    void setMember(const QJsonObject &member);
    void setMentionChannels(const QJsonArray &mentionChannels);
    void setMentionEveryone(const QJsonValue &mentionEveryone);
    void setMentionRoles(const QJsonArray &mentionRoles);
    void setMentions(const QJsonArray &mentions);
    void setMessageReference(const QJsonObject &value);
    void setNonce(const QJsonValue &value);
    void setPinned(const QJsonValue &pinned);
    void setReactions(const QJsonArray &ractions);
    void setTimestamp(const QJsonValue &timestamp);
    void setTTS(const QJsonValue &tts);
    void setType(const QJsonValue &type);
    void setWebhookId(const QJsonValue &webhookId);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    Q_PROPERTY(QJsonObject member READ getMember WRITE setMember)
    Q_PROPERTY(QJsonValue content READ getContent WRITE setContent)
    Q_PROPERTY(QJsonValue timestamp READ getTimestamp WRITE setTimestamp)
    Q_PROPERTY(QJsonValue edited_timestamp READ getEditedTimestamp WRITE setEditedTimestamp)
    Q_PROPERTY(QJsonValue tts READ getTTS WRITE setTTS)
    Q_PROPERTY(QJsonValue mention_everyone READ getMentionEveryone WRITE setMentionEveryone)
    Q_PROPERTY(QJsonArray mentions READ getMentions WRITE setMentions)
    Q_PROPERTY(QJsonArray mention_roles READ getMentionRoles WRITE setMentionRoles)
    Q_PROPERTY(QJsonArray mention_channels READ getMentionChannels WRITE setMentionChannels)
    Q_PROPERTY(QJsonArray attachments READ getAttachments WRITE setAttachments)
    Q_PROPERTY(QJsonArray embeds READ getEmbeds WRITE setEmbeds)
    Q_PROPERTY(QJsonArray reactions READ getReactions WRITE setReactions)
    Q_PROPERTY(QJsonValue nonce READ getNonce WRITE setNonce)
    Q_PROPERTY(QJsonValue pinned READ getPinned WRITE setPinned)
    Q_PROPERTY(QJsonValue webhook_id READ getWebhookId WRITE setWebhookId)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonObject activity READ getActivity WRITE setActivity)
    Q_PROPERTY(QJsonObject application READ getApplication WRITE setApplication)
    Q_PROPERTY(QJsonObject message_reference READ getMessageReference WRITE setMessageReference)
    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
};

Q_DECLARE_METATYPE(Message)

#endif // MESSAGE_H
