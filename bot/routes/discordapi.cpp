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

#include "discordapi.h"

#include "channeleditmessage.h"
#include "channelcreatemessage.h"
#include "channelcreatereaction.h"
#include "channelcrosspostmessage.h"
#include "channeldeleteallreactions.h"
#include "channeldeleteallreactionsforemoji.h"
#include "channeldeletechannel.h"
#include "channeldeleteownreaction.h"
#include "channeldeleteuserreaction.h"
#include "channelgetchannel.h"
#include "channelgetchannelmessage.h"
#include "channelgetchannelmessages.h"
#include "channelgetreactions.h"
#include "channelmodifychannel.h"
#include "channeldeletemessage.h"
#include "channelbulkmessagesdelete.h"
#include "channeleditchannelpermissions.h"
#include "channelgetchannelinvites.h"
#include "channelcreatechannelinvite.h"
#include "channeldeletechannelpermission.h"
#include "channelfollownewschannel.h"
#include "channeltriggertypingindicator.h"
#include "channelgetpinnedmessages.h"
#include "channeladdpinnedchannelmessage.h"
#include "channeldeletepinnedchannelmessage.h"
#include "guildcreateguild.h"
#include "guildgetguild.h"
#include "guildmodifyguild.h"
#include "guilddeleteguild.h"
#include "guildgetguildchannels.h"
#include "guildcreateguildchannel.h"
#include "guildmodifyguildchannelposition.h"
#include "guildgetguildmember.h"
#include "guildlistguildmembers.h"
#include "guildaddguildmember.h"
#include "guildmodifyguildmember.h"
#include "guildmodifycurrentusernick.h"
#include "guildaddguildmemberrole.h"
#include "guildremoveguildmemberrole.h"
#include "guildremoveguildmember.h"
#include "guildgetguildbans.h"
#include "guildgetguildban.h"
#include "guildcreateguildban.h"
#include "guildremoveguildban.h"
#include "guildgetguildroles.h"
#include "guildcreateguildrole.h"
#include "guildmodifyguildroleposition.h"
#include "guildmodifyguildrole.h"
#include "guilddeleteguildrole.h"
#include "guildgetguildprunecount.h"
#include "guildbeginguildprune.h"
#include "guildgetguildvoiceregions.h"
#include "guildgetguildinvites.h"
#include "guildgetguildintegrations.h"
#include "guildcreateguildintegration.h"
#include "guildmodifyguildintegration.h"
#include "guilddeleteguildintegration.h"
#include "guildsyncguildintegration.h"
#include "guildgetguildwidgetsettings.h"
#include "guildgetguildembed.h"
#include "guildmodifyguildwidget.h"
#include "guildmodifyguildembed.h"
#include "guildgetvanityurl.h"
#include "guildgetwidgetimage.h"
#include "emojilistguildemojis.h"
#include "emojicreateguildemoji.h"
#include "emojideleteguildemoji.h"
#include "emojigetguildemoji.h"
#include "emojimodifyguildemoji.h"
#include "usergetcurrentuser.h"
#include "usergetuser.h"
#include "usermodifycurrentuser.h"
#include "usergetcurrentuserguilds.h"
#include "usergetuserdms.h"
#include "userleaveguild.h"
#include "usercreatedm.h"
#include "usergetuserconnections.h"
#include "webhookcreatewebhook.h"
#include "webhookgetchannelwebhooks.h"
#include "webhookgetguildwebhooks.h"
#include "webhookgetwebhook.h"
#include "webhookgetwebhookwithtoken.h"
#include "webhookmodifywebhook.h"
#include "webhookmodifywebhookwithtoken.h"
#include "webhookdeletewebhook.h"
#include "webhookdeletewebhookwithtoken.h"
#include "webhookexecutewebook.h"
#include "webhookexecuteslackcompatiblewebhook.h"
#include "webhookexecutegithubcompatiblewebhook.h"
#include "invitegetinvite.h"
#include "invitedeleteinvite.h"
#include "voicelistvoiceregions.h"
#include "guildgetguildwidget.h"
#include "auditgetguildauditlog.h"

#include <QEventLoop>
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>
#include <QtMath>

#include "payloads/ratelimit.h"
#include "util/httputils.h"


const QByteArray DiscordAPI::X_RATELIMIT_GLOBAL = "x-ratelimit-global";
const QByteArray DiscordAPI::X_RATELIMIT_RESET = "x-ratelimit-reset";
const QByteArray DiscordAPI::X_RATELIMIT_REMAINING = "x-ratelimit-remaining";
const QByteArray DiscordAPI::X_RATELIMIT_LIMIT = "x-ratelimit-limit";
const QByteArray DiscordAPI::X_RATELIMIT_BUCKET = "x-ratelimit-bucket";

qint64 DiscordAPI::_globalRequestResetAt = 1;

QMap<QString, QString> DiscordAPI::_bucketIdByRoute;
QMap<QString, QMap<QString, QSharedPointer<Bucket> > > DiscordAPI::_bucketMaps;
QReadWriteLock DiscordAPI::_discoveryLock;

QByteArray DiscordAPI::_botAuthHeaderName = QByteArray();
QByteArray DiscordAPI::_botAuthHeaderValue = QByteArray();

EventContext
DiscordAPI::buildRequestContext(const QVariant &contextVariant) {
    EventContext context;

    SerializationUtils::fromVariant(context, contextVariant);

    return context;
}

QVariant
DiscordAPI::buildResponseVariant(QSharedPointer<EventContext> apiResponse) {
    QVariant responseContext;

    if (apiResponse) {
        responseContext = SerializationUtils::toVariant(*apiResponse);
    }

    return responseContext;
}


QSharedPointer<EventContext>
DiscordAPI::processRoute(Route &route) {
    QNetworkAccessManager networkManager;

    QString routeWithMethod = route.getRouteWithMethod();

    QSharedPointer<EventContext> context;

    if (_bucketIdByRoute.contains(routeWithMethod)) {
        QString bucketId = _bucketIdByRoute[routeWithMethod];

        if (_bucketMaps[bucketId].contains(route.getMajorParamId())) {
            context = checkBucketAndExecute(networkManager, route);

        } else {
            context = createBucketAndExecute(networkManager, route);
        }
    } else {
        QReadLocker locker(&_discoveryLock);

        // Check that bucket wasnt added during a lock.
        if (_bucketIdByRoute.contains(routeWithMethod)) {
            context = checkBucketAndExecute(networkManager, route);

        } else {
            context = createBucketAndExecute(networkManager, route);
        }
    }

    if (!context) {
        _logger->debug(QString("There was no valid reponse calling: %1").arg(routeWithMethod));

        context = QSharedPointer<EventContext>(new EventContext);
    }

    return context;
}

QSharedPointer<EventContext>
DiscordAPI::checkBucketAndExecute(QNetworkAccessManager &networkManager, Route &route) {
    QString bucketId = _bucketIdByRoute[route.getRouteWithMethod()];

    QSharedPointer<Bucket> bucket = _bucketMaps[bucketId][route.getMajorParamId()];

    QSharedPointer<EventContext> context;

    if (bucket->canExecute()) {
        QSharedPointer<QNetworkReply> reply =
                QSharedPointer<QNetworkReply>(executeRoute(networkManager, route));

        QByteArray response(reply->readAll());

        _logger->trace("Discord API Response: " + response);

        updateBucket(bucket, reply, response);

        context = QSharedPointer<EventContext>(new EventContext(response));

    } else {
        _logger->warning(QString("Rate limit reached for bucket: %1:%2. Limit resets at: %3")
                                .arg(bucket->getRateLimitBucket(),
                                     bucket->getMajorId(),
                                     QDateTime::fromSecsSinceEpoch(bucket->getRateLimitReset()).toString()));
    }

    return context;
}

void
DiscordAPI::updateBucket(QSharedPointer<Bucket> bucket, QSharedPointer<QNetworkReply> reply, const QByteArray &response) {
    QWriteLocker locker(bucket->getLock());

    if (!validStatusCode(reply, response)) {
        return;
    }

    qint64 rateLimitReset = reply->rawHeader(X_RATELIMIT_RESET).toUInt();

    if (rateLimitReset >= bucket->getRateLimitReset()) {
        bucket->setRateLimitReset(rateLimitReset);

        bucket->setRateLimitLimit(reply->rawHeader(X_RATELIMIT_LIMIT).toInt());

        bucket->setRateLimitRemaining(reply->rawHeader(X_RATELIMIT_REMAINING).toInt());
    }

    _logger->trace(QString("Rate Limit updated for bucket: %1:%2. Rate Limit reimaining: %3/%4. Rate limit resets at: %5")
                   .arg(bucket->getRateLimitBucket())
                   .arg(bucket->getMajorId())
                   .arg(bucket->getRateLimitRemaining())
                   .arg(bucket->getRateLimitLimit())
                   .arg(QDateTime::fromSecsSinceEpoch(bucket->getRateLimitReset()).toString()));
}

bool
DiscordAPI::validStatusCode(QSharedPointer<QNetworkReply> reply, const QByteArray &response) {
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    bool isValid = true;

    if (statusCode < 200 || (statusCode >= 300 && statusCode != 429)) {
        _logger->debug(QString("Discord API Call returned a problematic return code (%1): %2")
                        .arg(QString::number(statusCode), QString(response)));

        isValid = false;
    } else if (statusCode == 429) {
        RateLimit limit(response);

        if (limit.getGlobal().toBool()) {
            int resetAfter = qCeil(limit.getRetryAfter().toDouble());

            _globalRequestResetAt = QDateTime::currentSecsSinceEpoch() + resetAfter;
        }

        isValid = false;
    }

    return isValid;
}

QSharedPointer<EventContext>
DiscordAPI::createBucketAndExecute(QNetworkAccessManager &networkManager, Route &route) {
    QSharedPointer<EventContext> context;

    QSharedPointer<QNetworkReply> reply = executeRoute(networkManager, route);

    if (!reply) {
        return context;
    }

    QByteArray response = reply->readAll();

    if (!validStatusCode(reply, response)) {
        return context;
    }

    context = QSharedPointer<EventContext>(new EventContext(response));

    createBucket(reply, route);

    return context;
}

void
DiscordAPI::createBucket(QSharedPointer<QNetworkReply> reply, Route &route) {
    QString rateLimitBucket;

    QString majorParamId;

    if(reply->hasRawHeader(X_RATELIMIT_BUCKET)) {
        rateLimitBucket = QString(reply->rawHeader(X_RATELIMIT_BUCKET));

        majorParamId = route.getMajorParamId();

    } else {
        rateLimitBucket = GLOBAL_BUCKET;

        majorParamId = GLOBAL_BUCKET;
    }

    if (!_bucketMaps.contains(rateLimitBucket)) {
        QMap<QString, QSharedPointer<Bucket> > bucketMap;

        bucketMap[majorParamId] = createNewBucket(majorParamId, rateLimitBucket, reply);

        _bucketMaps[rateLimitBucket] = bucketMap;

    } else if (!_bucketMaps[rateLimitBucket].contains(majorParamId)) {
        _bucketMaps[rateLimitBucket][majorParamId] = createNewBucket(majorParamId, rateLimitBucket, reply);
    }

    _bucketIdByRoute[route.getRouteWithMethod()] = rateLimitBucket;
}

bool
DiscordAPI::isGlobalLimitActive() const {
    if (QDateTime::currentSecsSinceEpoch() < _globalRequestResetAt) {
        _logger->warning(QString("You are being globally rate limited, reset at: %1")
                         .arg(QDateTime::fromSecsSinceEpoch(_globalRequestResetAt).toString()));

        return true;
    }

    return false;
}

QSharedPointer<Bucket>
DiscordAPI::createNewBucket(const QString &majorId, const QString &rateLimitBucket, QSharedPointer<QNetworkReply> reply) {
    QSharedPointer<Bucket> bucket = QSharedPointer<Bucket>(new Bucket(majorId, rateLimitBucket));

    bucket->setRateLimitRemaining(reply->rawHeader(X_RATELIMIT_REMAINING).toInt());

    bucket->setRateLimitLimit(reply->rawHeader(X_RATELIMIT_LIMIT).toInt());

    bucket->setRateLimitReset(reply->rawHeader(X_RATELIMIT_RESET).toUInt());

    _logger->trace(QString("Bucket created for: %1:%2. Rate Limit reimaining: %3/%4. Rate limit resets at: %5")
                   .arg(bucket->getRateLimitBucket())
                   .arg(bucket->getMajorId())
                   .arg(bucket->getRateLimitRemaining())
                   .arg(bucket->getRateLimitLimit())
                   .arg(QDateTime::fromSecsSinceEpoch(bucket->getRateLimitReset()).toString()));

    return bucket;
}

QSharedPointer<QNetworkReply>
DiscordAPI::executeRoute(QNetworkAccessManager &networkManager, Route &route) {
    if (isGlobalLimitActive()) {
        return nullptr;
    }

    QNetworkReply *rawReply = nullptr;

    route.addRawHeader(_botAuthHeaderName, _botAuthHeaderValue);

    switch (route.getType()) {
        case Route::GET: {
            rawReply = networkManager.get(route.request());
            break;
        } case Route::POST: {
            QHttpMultiPart *multipPart = route.getHttpMultiPart();

            if (multipPart) {
                rawReply = networkManager.post(route.request(), route.getHttpMultiPart());
            } else {
                rawReply = networkManager.post(route.request(), route.payload());
            }
            break;
        } case Route::PUT: {
            rawReply = networkManager.put(route.request(), route.payload());
            break;
        } case Route::PATCH: {
            rawReply = networkManager.sendCustomRequest(route.request(), "PATCH", route.payload());
            break;
        } case Route::DELETE: {
            rawReply = networkManager.deleteResource(route.request());
            break;
        }
    }

    QSharedPointer<QNetworkReply> reply(rawReply);   

    HttpUtils::waitForReply(reply);

    return reply;
}

QVariant
DiscordAPI::channelGetChannel(const QVariant &context) {
    ChannelGetChannel getChannel(buildRequestContext(context));

    return buildResponseVariant(processRoute(getChannel));
}

QVariant
DiscordAPI::channelModifyChannel(const QVariant &context) {
    ChannelModifyChannel modifyChannel(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyChannel));
}

QVariant
DiscordAPI::channelDeleteChannel(const QVariant &context) {
    ChannelDeleteChannel deleteChannel(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteChannel));
}

QVariant
DiscordAPI::channelGetChannelMessages(const QVariant &context) {
    ChannelGetChannelMessages getChannelMessages(buildRequestContext(context));

    return buildResponseVariant(processRoute(getChannelMessages));
}

QVariant
DiscordAPI::channelGetChannelMessage(const QVariant &context) {
    ChannelGetChannelMessage getChannelMessage(buildRequestContext(context));

    return buildResponseVariant(processRoute(getChannelMessage));
}

QVariant
DiscordAPI::channelCreateMessage(const QVariant &contextVar, const QVariantList &files) {
    ChannelCreateMessage createMessage(buildRequestContext(contextVar), files);

    QSharedPointer<EventContext> apiResponse = processRoute(createMessage);

    apiResponse->processEventParams(GatewayEvent::MESSAGE_CREATE, EventContext::MESSAGE_ID);

    return buildResponseVariant(apiResponse);
}

QVariant
DiscordAPI::channelCrosspostMessage(const QVariant &context) {
    ChannelCrosspostMessage crosspostMessage(buildRequestContext(context));

    QSharedPointer<EventContext> apiResponse = processRoute(crosspostMessage);

    apiResponse->processEventParams(GatewayEvent::MESSAGE_CREATE, EventContext::MESSAGE_ID);

    return buildResponseVariant(apiResponse);
}

QVariant
DiscordAPI::channelCreateReaction(const QVariant &context) {
    ChannelCreateReaction createReaction(buildRequestContext(context));

    QSharedPointer<EventContext> apiResponse = processRoute(createReaction);

    apiResponse->processEventParams(GatewayEvent::MESSAGE_REACTION_ADD);

    return buildResponseVariant(apiResponse);
}

QVariant
DiscordAPI::channelDeleteOwnReaction(const QVariant &context) {
    ChannelDeleteOwnReaction deleteOwnReaction(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteOwnReaction));
}

QVariant
DiscordAPI::channelDeleteUserReaction(const QVariant &context) {
    ChannelDeleteUserReaction deleteUserReaction(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteUserReaction));
}

QVariant
DiscordAPI::channelGetReactions(const QVariant &context) {
    ChannelGetReactions getReactions(buildRequestContext(context));

    return buildResponseVariant(processRoute(getReactions));
}

QVariant
DiscordAPI::channelDeleteAllReactions(const QVariant &context) {
    ChannelDeleteAllReactions deleteAllReactions(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteAllReactions));
}

QVariant
DiscordAPI::channelDeleteAllReactionsForEmoji(const QVariant &context) {
    ChannelDeleteAllReactionsForEmoji deleteAllReactionsForEmoji(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteAllReactionsForEmoji));
}

QVariant
DiscordAPI::channelEditMessage(const QVariant &context) {        
    ChannelEditMessage editMessage(buildRequestContext(context));

    QSharedPointer<EventContext> apiResponse = processRoute(editMessage);

    apiResponse->processEventParams(GatewayEvent::MESSAGE_UPDATE, EventContext::MESSAGE_ID);

    return buildResponseVariant(apiResponse);
}

QVariant
DiscordAPI::channelDeleteMessage(const QVariant &context) {
    ChannelDeleteMessage deleteMessage(buildRequestContext(context));

    QSharedPointer<EventContext> apiResponse = processRoute(deleteMessage);

    apiResponse->processEventParams(GatewayEvent::MESSAGE_DELETE, EventContext::MESSAGE_ID);

    return buildResponseVariant(apiResponse);
}

QVariant
DiscordAPI::channelBulkDeleteMessages(const QVariant &context) {
    ChannelBulkDeleteMessages bulkDeleteMessage(buildRequestContext(context));

    QSharedPointer<EventContext> apiResponse = processRoute(bulkDeleteMessage);

    apiResponse->setEventName(GatewayEvent::MESSAGE_DELETE_BULK);

    return buildResponseVariant(apiResponse);
}

QVariant
DiscordAPI::channelEditChannelPermissions(const QVariant &context) {
    ChannelEditChannelPermissions editChannelPermissions(buildRequestContext(context));

    return buildResponseVariant(processRoute(editChannelPermissions));
}

QVariant
DiscordAPI::channelGetChannelInvites(const QVariant &context) {
    ChannelGetChannelInvites getChannelInvites(buildRequestContext(context));

    return buildResponseVariant(processRoute(getChannelInvites));
}

QVariant
DiscordAPI::channelCreateChannelInvite(const QVariant &context) {
    ChannelCreateChannelInvite createChannelInvite(buildRequestContext(context));

    return buildResponseVariant(processRoute(createChannelInvite));
}

QVariant
DiscordAPI::channelDeleteChannelPermission(const QVariant &context) {
    ChannelDeleteChannelPermission deleteChannelPermission(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteChannelPermission));
}

QVariant
DiscordAPI::channelFollowNewsChannel(const QVariant &context) {
    ChannelFollowNewsChannel followNewsChannel(buildRequestContext(context));

    return buildResponseVariant(processRoute(followNewsChannel));
}

QVariant
DiscordAPI::channelTriggerTypingIndicator(const QVariant &context) {
    ChannelTriggerTypingIndicator triggerTypingIndicator(buildRequestContext(context));

    return buildResponseVariant(processRoute(triggerTypingIndicator));
}

QVariant
DiscordAPI::channelGetPinnedMessages(const QVariant &context) {
    ChannelGetPinnedMessages getPinnedMessages(buildRequestContext(context));

    return buildResponseVariant(processRoute(getPinnedMessages));
}

QVariant
DiscordAPI::channelAddPinnedChannelMessage(const QVariant &context) {
    ChannelAddPinnedChannelMessage addPinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(processRoute(addPinnedChannelMessage));
}

QVariant
DiscordAPI::channelDeletePinnedChannelMessage(const QVariant &context) {
    ChannelDeletePinnedChannelMessage deletePinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(processRoute(deletePinnedChannelMessage));
}

QVariant
DiscordAPI::channelGroupDmAddRecipient(const QVariant &context) {
    ChannelDeletePinnedChannelMessage deletePinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(processRoute(deletePinnedChannelMessage));
}

QVariant
DiscordAPI::channelGroupDmRemoveRecipient(const QVariant &context) {
    ChannelDeletePinnedChannelMessage deletePinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(processRoute(deletePinnedChannelMessage));
}

QVariant
DiscordAPI::guildCreateGuild(const QVariant &context) {
    GuildCreateGuild createGuild(buildRequestContext(context));

    return buildResponseVariant(processRoute(createGuild));
}

QVariant
DiscordAPI::guildGetGuild(const QVariant &context) {
    GuildGetGuild getGuild(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuild));
}

QVariant
DiscordAPI::guildGetGuildPreview(const QVariant &context) {
    GuildGetGuild getGuild(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuild));
}

QVariant
DiscordAPI::guildModifyGuild(const QVariant &context) {
    GuildModifyGuild modifyGuild(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuild));
}

QVariant
DiscordAPI::guildDeleteGuild(const QVariant &context) {
    GuildDeleteGuild deleteGuild(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteGuild));
}

QVariant
DiscordAPI::guildGetGuildChannels(const QVariant &context) {
    GuildGetGuildChannels getGuildChannels(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildChannels));
}

QVariant
DiscordAPI::guildCreateGuildChannel(const QVariant &context) {
    GuildCreateGuildChannel createGuildChannel(buildRequestContext(context));

    return buildResponseVariant(processRoute(createGuildChannel));
}

QVariant
DiscordAPI::guildModifyGuildChannelPosition(const QVariant &context) {
    GuildModifyGuildChannelPosition modifyGuildChannelPosition(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildChannelPosition));
}

QVariant
DiscordAPI::guildGetGuildMember(const QVariant &context) {
    GuildGetGuildMember getGuildMember(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildMember));
}

QVariant
DiscordAPI::guildListGuildMembers(const QVariant &context) {
    GuildListGuildMembers listGuildMembers(buildRequestContext(context));

    return buildResponseVariant(processRoute(listGuildMembers));
}

QVariant
DiscordAPI::guildAddGuildMember(const QVariant &context) {
    GuildAddGuildMember addGuildMember(buildRequestContext(context));

    return buildResponseVariant(processRoute(addGuildMember));
}

QVariant
DiscordAPI::guildModifyGuildMember(const QVariant &context) {
    GuildModifyGuildMember modifyGuildMember(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildMember));
}

QVariant
DiscordAPI::guildModifyCurrentUserNick(const QVariant &context) {
    GuildModifyCurrentUserNick modifyCurrentUserNick(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyCurrentUserNick));
}

QVariant
DiscordAPI::guildAddGuildMemberRole(const QVariant &context) {
    GuildAddGuildMemberRole addGuildMemberRole(buildRequestContext(context));

    return buildResponseVariant(processRoute(addGuildMemberRole));
}

QVariant
DiscordAPI::guildRemoveGuildMemberRole(const QVariant &context) {
    GuildRemoveGuildMemberRole removeGuildMemberRole(buildRequestContext(context));

    return buildResponseVariant(processRoute(removeGuildMemberRole));
}

QVariant
DiscordAPI::guildRemoveGuildMember(const QVariant &context) {
    GuildRemoveGuildMember removeGuildMember(buildRequestContext(context));

    return buildResponseVariant(processRoute(removeGuildMember));
}

QVariant
DiscordAPI::guildGetGuildBans(const QVariant &context) {
    GuildGetGuildBans getGuildBans(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildBans));
}

QVariant
DiscordAPI::guildGetGuildBan(const QVariant &context) {
    GuildGetGuildBan getGuildBan(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildBan));
}

QVariant
DiscordAPI::guildCreateGuildBan(const QVariant &context) {
    GuildCreateGuildBan createGuildBan(buildRequestContext(context));

    return buildResponseVariant(processRoute(createGuildBan));
}

QVariant
DiscordAPI::guildRemoveGuildBan(const QVariant &context) {
    GuildRemoveGuildBan removeGuildBan(buildRequestContext(context));

    return buildResponseVariant(processRoute(removeGuildBan));
}

QVariant
DiscordAPI::guildGetGuildRoles(const QVariant &context) {
    GuildGetGuildRoles getGuildRoles(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildRoles));
}

QVariant
DiscordAPI::guildCreateGuildRole(const QVariant &context) {
    GuildCreateGuildRole createGuildRole(buildRequestContext(context));

    return buildResponseVariant(processRoute(createGuildRole));
}

QVariant
DiscordAPI::guildModifyGuildRolePosition(const QVariant &context) {
    GuildModifyGuildRolePosition modifyGuildRolePosition(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildRolePosition));
}

QVariant
DiscordAPI::guildModifyGuildRole(const QVariant &context) {
    GuildModifyGuildRole modifyGuildRole(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildRole));
}

QVariant
DiscordAPI::guildDeleteGuildRole(const QVariant &context) {
    GuildDeleteGuildRole modifyGuildRole(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildRole));
}

QVariant
DiscordAPI::guildGetGuildPruneCount(const QVariant &context) {
    GuildGetGuildPruneCount getGuildPruneCount(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildPruneCount));
}

QVariant
DiscordAPI::guildBeginGuildPrune(const QVariant &context) {
    GuildBeginGuildPrune beginGuildPrune(buildRequestContext(context));

    return buildResponseVariant(processRoute(beginGuildPrune));
}

QVariant
DiscordAPI::guildGetGuildVoiceRegions(const QVariant &context) {
    GuildGetGuildVoiceRegions getGuildVoiceRegions(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildVoiceRegions));
}

QVariant
DiscordAPI::guildGetGuildInvites(const QVariant &context) {
    GuildGetGuildInvites getGuildInvites(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildInvites));
}

QVariant
DiscordAPI::guildGetGuildIntegrations(const QVariant &context) {
    GuildGetGuildIntegrations getGuildIntegrations(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildIntegrations));
}

QVariant
DiscordAPI::guildCreateGuildIntegration(const QVariant &context) {
    GuildCreateGuildIntegration createGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(processRoute(createGuildIntegration));
}

QVariant
DiscordAPI::guildModifyGuildIntegration(const QVariant &context) {
    GuildModifyGuildIntegration modifyGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildIntegration));
}

QVariant
DiscordAPI::guildDeleteGuildIntegration(const QVariant &context) {
    GuildDeleteGuildIntegration deleteGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteGuildIntegration));
}

QVariant
DiscordAPI::guildSyncGuildIntegration(const QVariant &context) {
    GuildSyncGuildIntegration syncGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(processRoute(syncGuildIntegration));
}

QVariant
DiscordAPI::guildGetGuildWidget(const QVariant &context) {
    GuildGetGuildWidget getGuildWidget(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildWidget));
}

QVariant
DiscordAPI::guildGetGuildWidgetSettings(const QVariant &context) {
    GuildGetGuildWidgetSettings getGuildWidgetSettings(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildWidgetSettings));
}

QVariant
DiscordAPI::guildGetGuildEmbed(const QVariant &context) {
    GuildGetGuildEmbed getGuildEmbed(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildEmbed));
}

QVariant
DiscordAPI::guildModifyGuildWidget(const QVariant &context) {
    GuildModifyGuildWidget modifyGuildWidget(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildWidget));
}

QVariant
DiscordAPI::guildModifyGuildEmbed(const QVariant &context) {
    GuildModifyGuildEmbed modifyGuildEmbed(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildEmbed));
}

QVariant
DiscordAPI::guildGetVanityUrl(const QVariant &context) {
    GuildGetVanityUrl getVanityUrl(buildRequestContext(context));

    return buildResponseVariant(processRoute(getVanityUrl));
}

QVariant
DiscordAPI::guildGetWidgetImage(const QVariant &context) {
    GuildGetWidgetImage getWidgetImage(buildRequestContext(context));

    return buildResponseVariant(processRoute(getWidgetImage));
}

QVariant
DiscordAPI::emojiListGuildEmojis(const QVariant &context) {
    EmojiListGuildEmojis listGuildEmojis(buildRequestContext(context));

    return buildResponseVariant(processRoute(listGuildEmojis));
}

QVariant
DiscordAPI::emojiCreateGuildEmoji(const QVariant &context) {
    EmojiCreateGuildEmoji createGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(processRoute(createGuildEmoji));
}

QVariant
DiscordAPI::emojiDeleteGuildEmoji(const QVariant &context) {
    EmojiDeleteGuildEmoji deleteGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteGuildEmoji));
}

QVariant
DiscordAPI::emojiGetGuildEmoji(const QVariant &context) {
    EmojiGetGuildEmoji getGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildEmoji));
}

QVariant
DiscordAPI::emojiModifyGuildEmoji(const QVariant &context) {
    EmojiModifyGuildEmoji modifyGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyGuildEmoji));
}

QVariant
DiscordAPI::userGetCurrentUser(const QVariant &context) {
    UserGetCurrentUser getCurrentUser(buildRequestContext(context));

    return buildResponseVariant(processRoute(getCurrentUser));
}

QVariant
DiscordAPI::userGetUser(const QVariant &context) {
    UserGetUser getUser(buildRequestContext(context));

    return buildResponseVariant(processRoute(getUser));
}

QVariant
DiscordAPI::userModifyCurrentUser(const QVariant &context) {
    UserModifyCurrentUser modifyCurrentUser(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyCurrentUser));
}

QVariant
DiscordAPI::userGetCurrentUserGuilds(const QVariant &context) {
    UserCurrentGetUserGuilds getUserGuilds(buildRequestContext(context));

    return buildResponseVariant(processRoute(getUserGuilds));
}

QVariant
DiscordAPI::userGetUserDms(const QVariant &context) {
    UserGetUserDms getUserDms(buildRequestContext(context));

    return buildResponseVariant(processRoute(getUserDms));
}

QVariant
DiscordAPI::userLeaveGuild(const QVariant &context) {
    UserLeaveGuild leaveGuild(buildRequestContext(context));

    return buildResponseVariant(processRoute(leaveGuild));
}

QVariant
DiscordAPI::userCreateDm(const QVariant &context) {
    UserCreateDm createDm(buildRequestContext(context));

    return buildResponseVariant(processRoute(createDm));
}

QVariant
DiscordAPI::userGetUserConnections(const QVariant &context) {
    UserGetUserConnections getUserConnections(buildRequestContext(context));

    return buildResponseVariant(processRoute(getUserConnections));
}

QVariant
DiscordAPI::webhookCreateWebhook(const QVariant &context) {
    WebhookCreateWebhook createWebhook(buildRequestContext(context));

    return buildResponseVariant(processRoute(createWebhook));
}

QVariant
DiscordAPI::webhookGetChannelWebhooks(const QVariant &context) {
    WebhookGetChannelWebhooks getChannelWebhooks(buildRequestContext(context));

    return buildResponseVariant(processRoute(getChannelWebhooks));
}

QVariant
DiscordAPI::webhookGetGuildWebhooks(const QVariant &context) {
    WebhookGetGuildWebhooks getGuildWebhooks(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildWebhooks));
}

QVariant
DiscordAPI::webhookGetWebhook(const QVariant &context) {
    WebhookGetWebhook getWebhook(buildRequestContext(context));

    return buildResponseVariant(processRoute(getWebhook));
}

QVariant
DiscordAPI::webhookGetWebhookWithToken(const QVariant &context) {
    WebhookGetWebhookWithToken getWebhookWithToken(buildRequestContext(context));

    return buildResponseVariant(processRoute(getWebhookWithToken));
}

QVariant
DiscordAPI::webhookModifyWebhook(const QVariant &context) {
    WebhookModifyWebhook modifyWebhook(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyWebhook));
}

QVariant
DiscordAPI::webhookModifyWebhookWithToken(const QVariant &context) {
    WebhookModifyWebhookWithToken modifyWebhookWithToken(buildRequestContext(context));

    return buildResponseVariant(processRoute(modifyWebhookWithToken));
}

QVariant
DiscordAPI::webhookDeleteWebhook(const QVariant &context) {
    WebhookDeleteWebhook deleteWebhook(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteWebhook));
}

QVariant
DiscordAPI::webhookDeleteWebhookWithToken(const QVariant &context) {
    WebhookDeleteWebhookWithToken deleteWebhookWithToken(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteWebhookWithToken));
}

QVariant
DiscordAPI::webhookExecuteWebhook(const QVariant &context) {
    WebhookExecuteWebhook executeWebhook(buildRequestContext(context));

    return buildResponseVariant(processRoute(executeWebhook));
}

QVariant
DiscordAPI::webhookExecuteSlackCompatibleWebhook(const QVariant &context) {
    WebhookExecuteSlackCompatibleWebhook executeSlackCompatibleWebhook(buildRequestContext(context));

    return buildResponseVariant(processRoute(executeSlackCompatibleWebhook));
}

QVariant
DiscordAPI::webhookExecuteGithubCompatibleWebhook(const QVariant &context) {
    WebhookExecuteGithubCompatibleWebhook executeGithubCompatibleWebhook(buildRequestContext(context));

    return buildResponseVariant(processRoute(executeGithubCompatibleWebhook));
}

QVariant
DiscordAPI::inviteGetInvite(const QVariant &context) {
    InviteGetInvite getInvite(buildRequestContext(context));

    return buildResponseVariant(processRoute(getInvite));
}

QVariant
DiscordAPI::inviteDeleteInvite(const QVariant &context) {
    InviteDeleteInvite deleteInvite(buildRequestContext(context));

    return buildResponseVariant(processRoute(deleteInvite));
}

QVariant
DiscordAPI::voiceListVoiceRegions(const QVariant &context) {
    VoiceListVoiceRegions listVoiceRegions(buildRequestContext(context));

    return buildResponseVariant(processRoute(listVoiceRegions));
}

QVariant
DiscordAPI::auditGetGuildAuditLog(const QVariant &context) {
    AuditGetGuildAuditLog getGuildAuditLog(buildRequestContext(context));

    return buildResponseVariant(processRoute(getGuildAuditLog));
}

