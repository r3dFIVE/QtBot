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

#ifndef EVENTCONTEXT_H
#define EVENTCONTEXT_H

#include <QObject>

#include "payloads/jsonserializable.h"
#include "util/gatewayevent.h"


class EventContext : public JsonSerializable
{
    Q_OBJECT

    void buildContext(const QJsonObject &json);

public:

    static const QString ID;
    static const QString EMOJI;
    static const QString EVENT_NAME;
    static const QString CHANNEL_ID;
    static const QString GUILD_ID;
    static const QString INTEGRATION_ID;
    static const QString INVITE_CODE;
    static const QString ROLES;
    static const QString ROLE_ID;
    static const QString ROLE_IDS;
    static const QString MESSAGE_ID;
    static const QString OVERWRITE_ID;
    static const QString WEBHOOK_ID;
    static const QString WEBHOOK_TOKEN;
    static const QString USER_ID;
    static const QString JOB_ID;
    static const QString CONTENT;
    static const QString MEMBER;
    static const QString ARGS;
    static const QString AUTHOR;
    static const QString USERNAME;
    static const QString QUERY_PARAMS;
    static const QString SOURCE_PAYLOAD;
    static const QString TARGET_PAYLOAD;

    EventContext(QObject *parent = nullptr) : JsonSerializable(parent) {
        _jsonObject[TARGET_PAYLOAD] = QJsonObject();
    }
    EventContext(const QByteArray &json, QObject *parent = nullptr);
    EventContext(const QJsonObject &json, QObject *parent = nullptr);
    EventContext(const EventContext &other, QObject *parent = nullptr);

    ~EventContext() {}

    EventContext &operator=(const EventContext &other) {
        buildContext(other._jsonObject);

        return *this;
    }

    void processEventParams(const GatewayEvent::Event event, const QString &mainParamKey = QString());

    Q_PROPERTY(QJsonArray args READ getArgs WRITE setArgs)
    Q_PROPERTY(QJsonValue emoji READ getEmoji WRITE setEmoji)
    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue invite_code READ getInviteCode WRITE setInviteCode)
    Q_PROPERTY(QJsonValue integration_id READ getIntegrationId WRITE setIntegrationId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue message_id READ getMessageId WRITE setMessageId)
    Q_PROPERTY(QJsonValue overwrite_id READ getOverwriteId WRITE setOverwriteId)
    Q_PROPERTY(QJsonValue webhook_id READ getWebhookId WRITE setWebhookId)
    Q_PROPERTY(QJsonValue webhook_token READ getWebhookToken WRITE setWebhookToken)
    Q_PROPERTY(QJsonValue user_id READ getUserId WRITE setUserId)
    Q_PROPERTY(QJsonValue role_id READ getRoleId WRITE setRoleId)
    Q_PROPERTY(QJsonArray role_ids READ getRoleIds WRITE setRoleIds)
    Q_PROPERTY(QJsonValue job_id READ getJobId WRITE setJobId)
    Q_PROPERTY(QJsonValue content READ getContent WRITE setContent)
    Q_PROPERTY(QJsonValue event_name READ getEventName WRITE setEventName)
    Q_PROPERTY(QJsonValue username READ getUsername WRITE setUsername)
    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    Q_PROPERTY(QJsonObject query_params READ getQueryParams WRITE setQueryParams)
    Q_PROPERTY(QJsonObject source_payload READ getSourcePayload WRITE setSourcePayload)
    Q_PROPERTY(QJsonObject target_payload READ getTargetPayload WRITE setTargetPayload)


    Q_INVOKABLE QJsonArray getArgs() const;
    Q_INVOKABLE QJsonArray getRoleIds() const;
    Q_INVOKABLE QJsonObject getAuthor() const;
    Q_INVOKABLE QJsonObject getQueryParams() const;
    Q_INVOKABLE QJsonObject getSourcePayload() const;
    Q_INVOKABLE QJsonObject getTargetPayload() const;
    Q_INVOKABLE QJsonValue getChannelId() const;
    Q_INVOKABLE QJsonValue getContent() const;
    Q_INVOKABLE QJsonValue getEmoji() const;
    Q_INVOKABLE QJsonValue getEventName() const;
    Q_INVOKABLE QJsonValue getMessageId() const;
    Q_INVOKABLE QJsonValue getOverwriteId() const;
    Q_INVOKABLE QJsonValue getGuildId() const;
    Q_INVOKABLE QJsonValue getJobId() const;
    Q_INVOKABLE QJsonValue getRoleId() const;
    Q_INVOKABLE QJsonValue getUserId() const;
    Q_INVOKABLE QJsonValue getUsername() const;
    Q_INVOKABLE QJsonValue getWebhookId() const;
    Q_INVOKABLE QJsonValue getWebhookToken() const;
    Q_INVOKABLE QJsonValue getIntegrationId() const;
    Q_INVOKABLE QJsonValue getInviteCode() const;
    Q_INVOKABLE void setArgs(const QJsonArray &args) const;
    Q_INVOKABLE void setAuthor(const QJsonObject &author);
    Q_INVOKABLE void setChannelId(const QJsonValue &channelId);
    Q_INVOKABLE void setContent(const QJsonValue &content);
    Q_INVOKABLE void setEmoji(const QJsonValue &emoji);
    Q_INVOKABLE void setEventName(const QJsonValue &eventName);
    Q_INVOKABLE void setGuildId(const QJsonValue &guildId);
    Q_INVOKABLE void setJobId(const QJsonValue &jobId);
    Q_INVOKABLE void setRoleId(const QJsonValue &roleId);
    Q_INVOKABLE void setRoleIds(const QJsonValue &roleIds);
    Q_INVOKABLE void setMessageId(const QJsonValue &messageId);
    Q_INVOKABLE void setOverwriteId(const QJsonValue &overwriteId);
    Q_INVOKABLE void setQueryParams(const QJsonObject &queryParams);
    Q_INVOKABLE void setSourcePayload(const QJsonObject &sourcePayload);
    Q_INVOKABLE void setTargetPayload(const QJsonObject &targetPayload);
    Q_INVOKABLE void setUserId(const QJsonValue &userId);
    Q_INVOKABLE void setUsername(const QJsonValue &username);
    Q_INVOKABLE void setIntegrationId(const QJsonValue &webhookId);
    Q_INVOKABLE void setInviteCode(const QJsonValue &inviteCode);
    Q_INVOKABLE void setWebhookId(const QJsonValue &webhookId);
    Q_INVOKABLE void setWebhookToken(const QJsonValue &webhookToken);
    Q_INVOKABLE void splitArgs();
};

Q_DECLARE_METATYPE(EventContext)

#endif // EVENTCONTEXT_H
