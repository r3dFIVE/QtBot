/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GUILD_H
#define GUILD_H

#include "jsonserializable.h"


class Guild : public JsonSerializable
{

    Q_OBJECT

public:

    enum DefaultNotificationlevel {
        ALL_MESSAGES,
        ONLY_MENTIONS
    };
    Q_ENUM(DefaultNotificationlevel)

    enum ExplicitContentFilterLevel {
        DISABLED,
        MEMBERS_WITHOUT_ROLES,
        ALL_MEMBERS
    };
    Q_ENUM(ExplicitContentFilterLevel)

    enum PremiumTierLevel {
        TIER_0,
        TIER_1,
        TIER_2,
        TIER_3
    };
    Q_ENUM(PremiumTierLevel)

    enum VerificationLevel {
        NONE,
        LOW,
        MEDIUM,
        HIGH,
        VERY_HIGH
    };
    Q_ENUM(VerificationLevel)

    static const QString ID;
    static const QString NAME;
    static const QString ICON;
    static const QString SPLASH;
    static const QString DISCOVERY_SPLASH;
    static const QString OWNER;
    static const QString OWNER_ID;
    static const QString PERMISSIONS;
    static const QString REGION;
    static const QString AFK_CHANNEL_ID;
    static const QString AFK_TIMEOUT;
    static const QString EMBED_ENABLED;
    static const QString EMBED_CHANNEL_ID;
    static const QString VERIFICATION_LEVEL;
    static const QString DEFAULT_MESSAGE_NOTIFICATIONS;
    static const QString EXPLICIT_CONTENT_FILTER;
    static const QString ROLES;
    static const QString EMOJIS;
    static const QString FEATURES;
    static const QString MFA_LEVEL;
    static const QString APPLICATION_ID;
    static const QString WIDGET_ENABLED;
    static const QString WIDGET_CHANNEL_ID;
    static const QString SYSTEM_CHANNEL_ID;
    static const QString SYSTEM_CHANNEL_FLAGS;
    static const QString RULES_CHANNEL_ID;
    static const QString JOINED_AT;
    static const QString LARGE;
    static const QString UNAVAILABLE;
    static const QString MEMBER_COUNT;
    static const QString VOICE_STATES;
    static const QString MEMBERS;
    static const QString CHANNELS;
    static const QString PRESENCES;
    static const QString MAX_PRESENCES;
    static const QString MAX_MEMBERS;
    static const QString VANITY_URL_CODE;
    static const QString DESCRIPTION;
    static const QString BANNER;
    static const QString PREMIUM_TIER;
    static const QString PREMIUM_SUBSCRIPTION_COUNT;
    static const QString PREFERRED_LOCALE;
    static const QString PUBLIC_UPDATES_CHANNEL_ID;
    static const QString MAX_VIDEO_CHANNEL_USERS;
    static const QString APPROXIMATE_MEMBER_COUNT;
    static const QString APPROXIMATE_PRESENCE_COUNT;

    Guild() {}
    Guild(const QByteArray &json) : JsonSerializable(json) {}
    Guild(const QJsonObject &json) : JsonSerializable(json) {}
    Guild(const QString &json) : JsonSerializable(json) {}

    QJsonArray getChannels() const;
    QJsonArray getEmojis() const;
    QJsonArray getFeatures() const;
    QJsonArray getMembers() const;
    QJsonArray getPresences() const;
    QJsonArray getRoles() const;
    QJsonArray getVoiceStates() const;
    QJsonValue getAfkChannelId() const;
    QJsonValue getAfkTimeout() const;
    QJsonValue getApplicationId() const;
    QJsonValue getBanner() const;
    QJsonValue getDefaultMessageNotifications() const;
    QJsonValue getDescription() const;
    QJsonValue getDiscoverySplash() const;
    QJsonValue getEmbedChannelId() const;
    QJsonValue getEmbedEnabled() const;
    QJsonValue getExplicitContentFilter() const;
    QJsonValue getIcon() const;
    QJsonValue getId() const;
    QJsonValue getJoinedAt() const;
    QJsonValue getLarge() const;
    QJsonValue getApproximateMemberCount() const;
    QJsonValue getApproximatePresenceCount() const;
    QJsonValue getMaxMembers() const;
    QJsonValue getMaxPresences() const;
    QJsonValue getMaxVideoChannelUsers() const;
    QJsonValue getMfaLevel() const;
    QJsonValue getName() const;
    QJsonValue getMemberCount() const;
    QJsonValue getOwner() const;
    QJsonValue getOwnerId() const;
    QJsonValue getPermissions() const;
    QJsonValue getPreferredLocale() const;
    QJsonValue getPremiumTier() const;
    QJsonValue getPremiumSubscriptionCount() const;
    QJsonValue getPublicUpdatesChannelId() const;
    QJsonValue getRegion() const;
    QJsonValue getRulesChannelId() const;
    QJsonValue getSplash() const;
    QJsonValue getSystemChannelId() const;
    QJsonValue getSystemChannelFlags() const;
    QJsonValue getUnavailable() const;
    QJsonValue getVanityUrlCode() const;
    QJsonValue getVerificationLevel() const;
    QJsonValue getWidgetChannelId() const;
    QJsonValue getWidgetEnabled() const;
    void setId(const QJsonValue &id);
    void setName(const QJsonValue &name);
    void setIcon(const QJsonValue &icon);
    void setSplash(const QJsonValue &splash);
    void setDiscoverySplash(const QJsonValue &discoverySplash);
    void setOwner(const QJsonValue &owner);
    void setOwnerId(const QJsonValue &owner_id);
    void setPermissions(const QJsonValue &permissions);
    void setRegion(const QJsonValue &region);
    void setAfkChannelId(const QJsonValue &afkChannelId);
    void setAfkTimeout(const QJsonValue &afkTimeout);
    void setEmbedEnabled(const QJsonValue &embedEnabled);
    void setEmbedChannelId(const QJsonValue &embedChannelId);
    void setVerificationLevel(const QJsonValue &verificationLevel);
    void setDefaultMessageNotifications(const QJsonValue &defaultMessageNotifications);
    void setExplicitContentFilter(const QJsonValue &explicitContentFilter);
    void setRoles(const QJsonArray &roles) ;
    void setEmojis(const QJsonArray &emojis);
    void setFeatures(const QJsonArray &features);
    void setMfaLevel(const QJsonValue &mfaLevel);
    void setApplicationId(const QJsonValue &applicationId);
    void setWidgetEnabled(const QJsonValue &widgetEnabled);
    void setWidgetChannelId(const QJsonValue &widgetChannelId);
    void setSystemChannelId(const QJsonValue &systemChannelId);
    void setSystemChannelFlags(const QJsonValue &systemChannelFlags);
    void setRulesChannelId(const QJsonValue &rulesChannelId);
    void setJoinedAt(const QJsonValue &joinedAt);
    void setLarge(const QJsonValue &large);
    void setUnavailable(const QJsonValue &unavailable);
    void setMemberCount(const QJsonValue &memberCount);
    void setVoiceStates(const QJsonArray &voice_states);
    void setMembers(const QJsonArray &members);
    void setChannels(const QJsonArray &channels);
    void setPresences(const QJsonArray &presences);
    void setMaxPresences(const QJsonValue &maxPresences);
    void setMaxMembers(const QJsonValue &maxMembers);
    void setVanityUrlCode(const QJsonValue &vanityUrlCode);
    void setDescription(const QJsonValue &description);
    void setBanner(const QJsonValue &banner);
    void setPremiumTier(const QJsonValue &premium_tier);
    void setPremiumSubscriptionCount(const QJsonValue &premiumSubscriptionCount);
    void setPreferredLocale(const QJsonValue &preferredLocale);
    void setPublicUpdatesChannelId(const QJsonValue &publicUpdatesChannelId);
    void setMaxVideoChannelUsers(const QJsonValue &maxVideoChannelUsers);
    void setApproximateMemberCount(const QJsonValue &approximateMemberCount);
    void setApproximatePresenceCount(const QJsonValue &approximatePresenceCount);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue icon READ getIcon WRITE setIcon)
    Q_PROPERTY(QJsonValue splash READ getSplash WRITE setSplash)
    Q_PROPERTY(QJsonValue discovery_splash READ getDiscoverySplash WRITE setDiscoverySplash)
    Q_PROPERTY(QJsonValue owner READ getOwner WRITE setOwner)
    Q_PROPERTY(QJsonValue owner_id READ getOwnerId WRITE setOwnerId)
    Q_PROPERTY(QJsonValue permissions READ getPermissions WRITE setPermissions)
    Q_PROPERTY(QJsonValue region READ getRegion WRITE setRegion)
    Q_PROPERTY(QJsonValue afk_channel_id READ getAfkChannelId WRITE setAfkChannelId)
    Q_PROPERTY(QJsonValue afk_timeout READ getAfkTimeout WRITE setAfkTimeout)
    Q_PROPERTY(QJsonValue embed_enabled READ getEmbedEnabled WRITE setEmbedEnabled)
    Q_PROPERTY(QJsonValue embed_channel_id READ getEmbedChannelId WRITE setEmbedChannelId)
    Q_PROPERTY(QJsonValue verification_level READ getVerificationLevel WRITE setVerificationLevel)
    Q_PROPERTY(QJsonValue default_message_notifications READ getDefaultMessageNotifications WRITE setDefaultMessageNotifications)
    Q_PROPERTY(QJsonValue explicit_content_filter READ getExplicitContentFilter WRITE setExplicitContentFilter)
    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    Q_PROPERTY(QJsonArray emojis READ getEmojis WRITE setEmojis)
    Q_PROPERTY(QJsonArray features READ getFeatures WRITE setFeatures)
    Q_PROPERTY(QJsonValue mfa_level READ getMfaLevel WRITE setMfaLevel)
    Q_PROPERTY(QJsonValue application_id READ getApplicationId WRITE setApplicationId)
    Q_PROPERTY(QJsonValue widget_enabled READ getWidgetEnabled WRITE setWidgetEnabled)
    Q_PROPERTY(QJsonValue widget_channel_id READ getWidgetChannelId WRITE setWidgetChannelId)
    Q_PROPERTY(QJsonValue system_channel_id READ getSystemChannelId WRITE setSystemChannelId)
    Q_PROPERTY(QJsonValue system_channel_flags READ getSystemChannelFlags WRITE setSystemChannelFlags)
    Q_PROPERTY(QJsonValue rules_channel_id READ getRulesChannelId WRITE setRulesChannelId)
    Q_PROPERTY(QJsonValue joined_at READ getJoinedAt WRITE setJoinedAt)
    Q_PROPERTY(QJsonValue large READ getLarge WRITE setLarge)
    Q_PROPERTY(QJsonValue unavailable READ getUnavailable WRITE setUnavailable)
    Q_PROPERTY(QJsonValue member_count READ getMemberCount WRITE setMemberCount)
    Q_PROPERTY(QJsonArray voice_states READ getVoiceStates WRITE setVoiceStates)
    Q_PROPERTY(QJsonArray members READ getMembers WRITE setMembers)
    Q_PROPERTY(QJsonArray channels READ getChannels WRITE setChannels)
    Q_PROPERTY(QJsonArray presences READ getPresences WRITE setPresences)
    Q_PROPERTY(QJsonValue max_presences READ getMaxPresences WRITE setMaxPresences)
    Q_PROPERTY(QJsonValue max_members READ getMaxMembers WRITE setMaxMembers)
    Q_PROPERTY(QJsonValue vanity_url_code READ getVanityUrlCode WRITE setVanityUrlCode)
    Q_PROPERTY(QJsonValue description READ getDescription WRITE setDescription)
    Q_PROPERTY(QJsonValue banner READ getBanner WRITE setBanner)
    Q_PROPERTY(QJsonValue premium_tier READ getPremiumTier WRITE setPremiumTier)
    Q_PROPERTY(QJsonValue premium_subscription_count READ getPremiumSubscriptionCount WRITE setPremiumSubscriptionCount)
    Q_PROPERTY(QJsonValue preferred_locale READ getPreferredLocale WRITE setPreferredLocale)
    Q_PROPERTY(QJsonValue public_updates_channel_id READ getPublicUpdatesChannelId WRITE setPublicUpdatesChannelId)
    Q_PROPERTY(QJsonValue max_video_channel_users READ getMaxVideoChannelUsers WRITE setMaxVideoChannelUsers)
    Q_PROPERTY(QJsonValue approximate_member_count READ getApproximateMemberCount WRITE setApproximateMemberCount)
    Q_PROPERTY(QJsonValue approximate_presence_count READ getApproximatePresenceCount WRITE setApproximatePresenceCount)
};


Q_DECLARE_METATYPE(Guild)

#endif // GUILD_H
