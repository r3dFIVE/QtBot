#ifndef MESSAGE_H
#define MESSAGE_H

#include "attachment.h"
#include "channelmention.h"
#include "embed.h"
#include "guildmember.h"
#include "jsonserializable.h"
#include "reaction.h"
#include "user.h"
#include "messageactivity.h"
#include "messageapplication.h"
#include "messagereference.h"

#include <QObject>
#include <QSharedPointer>

class Message : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    QJsonValue id;

    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    QJsonValue channel_id;

    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    QJsonValue guild_id;

    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    QSharedPointer<User> author;

    Q_PROPERTY(QJsonObject member READ getMember WRITE setMember)
    QSharedPointer<GuildMember> member;

    Q_PROPERTY(QJsonValue content READ getContent WRITE setContent)
    QJsonValue content;

    Q_PROPERTY(QJsonValue timestamp READ getTimestamp WRITE setTimestamp)
    QJsonValue timestamp;

    Q_PROPERTY(QJsonValue edited_timestamp READ getEditedTimestamp WRITE setEditedTimestamp)
    QJsonValue edited_timestamp;

    Q_PROPERTY(QJsonValue tts READ getTts WRITE setTts)
    QJsonValue tts;

    Q_PROPERTY(QJsonValue mention_everyone READ getMentionEveryone WRITE setMentionEveryone)
    QJsonValue mention_everyone;

    Q_PROPERTY(QJsonArray mentions READ getMentions WRITE setMentions)
    QList<QSharedPointer<User>> mentions;

    Q_PROPERTY(QJsonArray mention_roles READ getMentionRoles WRITE setMentionRoles)
    QList<QString> mention_roles;

    Q_PROPERTY(QJsonArray mention_channels READ getMentionChannels WRITE setMentionChannels)
    QList<QSharedPointer<ChannelMention>> mention_channels;

    Q_PROPERTY(QJsonArray attachments READ getAttachments WRITE setAttachments)
    QList<QSharedPointer<Attachment>> attachments;

    Q_PROPERTY(QJsonArray embeds READ getEmbeds WRITE setEmbeds)
    QList<QSharedPointer<Embed>> embeds;

    Q_PROPERTY(QJsonArray reactions READ getReactions WRITE setReactions)
    QList<QSharedPointer<Reaction>> reactions;

    Q_PROPERTY(QJsonValue nonce READ getNonce WRITE setNonce)
    QJsonValue nonce;

    Q_PROPERTY(QJsonValue pinned READ getPinned WRITE setPinned)
    QJsonValue pinned;

    Q_PROPERTY(QJsonValue webhook_id READ getWebhookId WRITE setWebhookId)
    QJsonValue webhook_id;

    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    QJsonValue type;

    Q_PROPERTY(QJsonObject activity READ getActivity WRITE setActivity)
    QSharedPointer<MessageActivity> activity;

    Q_PROPERTY(QJsonObject application READ getApplication WRITE setApplication)
    QSharedPointer<MessageApplication> application;

    Q_PROPERTY(QJsonObject message_reference READ getMessageReference WRITE setMessageReference)
    QSharedPointer<MessageReference> message_reference;

    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
    QJsonValue flags;

    QJsonValue getId() const;
    void setId(const QJsonValue &value);
    QJsonValue getChannelId() const;
    void setChannelId(const QJsonValue &value);
    QJsonValue getGuildId() const;
    void setGuildId(const QJsonValue &value);
    QJsonObject getAuthor() const;
    void setAuthor(const QJsonObject &value);
    QJsonObject getMember() const;
    void setMember(const QJsonObject &value);
    QJsonValue getContent() const;
    void setContent(const QJsonValue &value);
    QJsonValue getTimestamp() const;
    void setTimestamp(const QJsonValue &value);
    QJsonValue getEditedTimestamp() const;
    void setEditedTimestamp(const QJsonValue &value);
    QJsonValue getTts() const;
    void setTts(const QJsonValue &value);
    QJsonValue getMentionEveryone() const;
    void setMentionEveryone(const QJsonValue &value);
    QJsonArray getMentions() const;
    void setMentions(const QJsonArray &values);
    QJsonArray getMentionRoles() const;
    void setMentionRoles(const QJsonArray &values);
    QJsonArray getMentionChannels() const;
    void setMentionChannels(const QJsonArray &values);
    QJsonArray getAttachments() const;
    void setAttachments(const QJsonArray &values);
    QJsonArray getEmbeds() const;
    void setEmbeds(const QJsonArray &values);
    QJsonArray getReactions() const;
    void setReactions(const QJsonArray &values);
    QJsonValue getNonce() const;
    void setNonce(const QJsonValue &value);
    QJsonValue getPinned() const;
    void setPinned(const QJsonValue &value);
    QJsonValue getWebhookId() const;
    void setWebhookId(const QJsonValue &value);
    QJsonValue getType() const;
    void setType(const QJsonValue &value);
    QJsonObject getActivity() const;
    void setActivity(const QJsonObject &value);
    QJsonObject getApplication() const;
    void setApplication(const QJsonObject &value);
    QJsonObject getMessageReference() const;
    void setMessageReference(const QJsonObject &value);
    QJsonValue getFlags() const;
    void setFlags(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    Message() {}
    ~Message() {}
};

Q_DECLARE_METATYPE(Message)

#endif // MESSAGE_H
