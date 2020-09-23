#ifndef DISCORDAPI_H
#define DISCORDAPI_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QQmlEngine>

#include "botjob/httpclient.h"


class DiscordAPI : public QObject
{
    Q_OBJECT

    static QString _botToken;

    HttpClient _httpClient;

    EventContext buildRequestContext(const QVariant &contextVariant);
    QVariant buildResponseVariant(QSharedPointer<EventContext> apiResponse);

public:        
    DiscordAPI() : _httpClient(_botToken) { }
    ~DiscordAPI() {}

    static void setBotToken(const QString &botToken);

    /*
     *      CHANNEL API FUNCTIONS
     *      https://discord.com/developers/docs/resources/channel
     */

    QVariant channelGetChannel(const QVariant &context);
    QVariant channelModifyChannel(const QVariant &context);
    QVariant channelDeleteChannel(const QVariant &context);
    QVariant channelGetChannelMessages(const QVariant &context);
    QVariant channelGetChannelMessage(const QVariant &context);
    QVariant channelCreateMessage(const QVariant &context);
    QVariant channelCrosspostMessage(const QVariant &context);
    QVariant channelCreateReaction(const QVariant &context);
    QVariant channelDeleteOwnReaction(const QVariant &context);
    QVariant channelDeleteUserReaction(const QVariant &context);
    QVariant channelGetReactions(const QVariant &context);
    QVariant channelDeleteAllReactions(const QVariant &context);
    QVariant channelDeleteAllReactionsForEmoji(const QVariant &context);
    QVariant channelEditMessage(const QVariant &context);
    QVariant channelDeleteMessage(const QVariant &context);
    QVariant channelBulkDeleteMessages(const QVariant &context);
    QVariant channelEditChannelPermissions(const QVariant &context);
    QVariant channelGetChannelInvites(const QVariant &context);
    QVariant channelCreateChannelInvite(const QVariant &context);
    QVariant channelDeleteChannelPermission(const QVariant &context);
    QVariant channelFollowNewsChannel(const QVariant &context);
    QVariant channelTriggerTypingIndicator(const QVariant &context);
    QVariant channelGetPinnedMessages(const QVariant &context);
    QVariant channelAddPinnedChannelMessage(const QVariant &context);
    QVariant channelDeletePinnedChannelMessage(const QVariant &context);
    QVariant channelGroupDmAddRecipient(const QVariant &context);
    QVariant channelGroupDmRemoveRecipient(const QVariant &context);

};

#endif // DISCORDAPI_H
