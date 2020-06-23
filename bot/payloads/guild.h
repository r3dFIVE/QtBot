#ifndef GUILD_H
#define GUILD_H

#include "channel.h"
#include "emoji.h"
#include "jsonserializable.h"
#include "presenceupdate.h"
#include "role.h"
#include "voicestate.h"


class Guild : public JsonSerializable
{

    Q_OBJECT

public:

    const QString ID = "id";
    const QString NAME = "name";
    const QString ICON = "icon";
    const QString SPLASH = "splash";
    const QString DISCOVERY_SPLASH = "discovery_splash";
    const QString OWNER = "owner";
    const QString OWNER_ID = "owner_id";
    const QString PERMISSIONS = "permission";
    const QString REGION = "region";
    const QString AFK_CHANNEL_ID = "afk_channel_id";
    const QString AFK_TIMEOUT = "afk_timeout";
    const QString EMBED_ENABLED = "embed_enabled";
    const QString EMBED_CHANNEL_ID = "embed_channel_id";
    const QString VERIFICATION_LEVEL = "verification_level";
    const QString DEFAULT_MESSAGE_NOTIFICATIONS = "default_message_notifications";
    const QString EXPLICIT_CONTENT_FILTER = "explicit_content_filter";
    const QString ROLES = "roles";
    const QString EMOJIS = "emojis";
    const QString FEATURES = "features";
    const QString MFA_LEVEL = "mfa_level";
    const QString APPLICATION_ID = "application_id";
    const QString WIDGET_ENABLED = "widget_enabled";
    const QString WIDGET_CHANNEL_ID = "widget_channel_id";
    const QString SYSTEM_CHANNEL_ID = "system_channel_id";
    const QString SYSTEM_CHANNEL_FLAGS = "system_channel_flags";
    const QString RULES_CHANNEL_ID = "rules_channel_id";
    const QString JOINED_AT = "joined_at";
    const QString LARGE = "large";
    const QString UNAVAILABLE = "unavailable";
    const QString MEMBER_COUNT = "member_count";
    const QString VOICE_STATES = "voice_states";
    const QString MEMBERS = "members";
    const QString CHANNELS = "channels";
    const QString PRESENCES = "presences";
    const QString MAX_PRESENCES = "max_presences";
    const QString MAX_MEMBERS = "max_members";
    const QString VANITY_URL_CODE = "vanity_url_code";
    const QString DESCRIPTION = "description";
    const QString BANNER = "banner";
    const QString PREMIUM_TIER = "premium_tier";
    const QString PREMIUM_SUBSCRIPTION_COUNT = "premium_subscription_count";
    const QString PREFERRED_LOCALE = "preferred_locale";
    const QString PUBLIC_UPDATES_CHANNEL_ID = "public_update_channel_id";
    const QString MAX_VIDEO_CHANNEL_USERS = "max_video_channel_users";
    const QString APPROXIMATE_MEMBER_COUNT = "approximate_member_count";
    const QString APPROXIMATE_PRESENCE_COUNT = "approximate_user_count";

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;

    Q_PROPERTY(QString icon READ getIcon WRITE setIcon)
    QString icon;

    Q_PROPERTY(QString splash READ getSplash WRITE setSplash)
    QString splash;

    Q_PROPERTY(QString discovery_splash READ getDiscoverySplash WRITE setDiscoverySplash)
    QString discovery_splash;

    Q_PROPERTY(QJsonValue owner READ getOwner WRITE setOwner)
    QSharedPointer<bool> owner;

    Q_PROPERTY(QString owner_id READ getOwnerId WRITE setOwnerId)
    QString owner_id;

    Q_PROPERTY(QJsonValue permissions READ getPermissions WRITE setPermissions)
    QSharedPointer<int> permissions;

    Q_PROPERTY(QString region READ getRegion WRITE setRegion)
    QString region;

    Q_PROPERTY(QString afk_channel_id READ getAfkChannelId WRITE setAfkChannelId)
    QString afk_channel_id;

    Q_PROPERTY(int afk_timeout READ getAfkTimeout WRITE setAfkTimeout)
    int afk_timeout;

    Q_PROPERTY(QJsonValue embed_enabled READ getEmbedEnabled WRITE setEmbedEnabled)
    QSharedPointer<bool> embed_enabled;

    Q_PROPERTY(QString embed_channel_id READ getEmbedChannelId WRITE setEmbedChannelId)
    QString embed_channel_id;

    Q_PROPERTY(int verification_level READ getVerificationLevel WRITE setVerificationLevel)
    int verification_level;

    Q_PROPERTY(int default_message_notifications READ getDefaultMessageNotifications WRITE setDefaultMessageNotifications)
    int default_message_notifications;

    Q_PROPERTY(int explicit_content_filter READ getExplicitContentFilter WRITE setExplicitContentFilter)
    int explicit_content_filter;

    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    QList<Role> roles;

    Q_PROPERTY(QJsonArray emojis READ getEmojis WRITE setEmojis)
    QList<Emoji> emojis;

    Q_PROPERTY(QJsonArray features READ getFeatures WRITE setFeatures)
    QList<QString> features;

    Q_PROPERTY(int mfa_level READ getMfaLevel WRITE setMfaLevel)
    int mfa_level;

    Q_PROPERTY(QString application_id READ getApplicationId WRITE setApplicationId)
    QString application_id;

    Q_PROPERTY(QJsonValue widget_enabled READ getWidgetEnabled WRITE setWidgetEnabled)
    QSharedPointer<bool> widget_enabled;

    Q_PROPERTY(QString widget_channel_id READ getWidgetChannelId WRITE setWidgetChannelId)
    QString widget_channel_id;

    Q_PROPERTY(QString system_channel_id READ getSystemChannelId WRITE setSystemChannelId)
    QString system_channel_id;

    Q_PROPERTY(QJsonValue system_channel_flags READ getSystemChannelFlags WRITE setSystemChannelFlags)
    QSharedPointer<int> system_channel_flags;

    Q_PROPERTY(QString rules_channel_id READ getRulesChannelId WRITE setRulesChannelId)
    QString rules_channel_id;

    Q_PROPERTY(QString joined_at READ getJoinedAt WRITE setJoinedAt)
    QString joined_at;

    Q_PROPERTY(QJsonValue large READ getLarge WRITE setLarge)
    QSharedPointer<bool> large;

    Q_PROPERTY(QJsonValue unavailable READ getUnavailable WRITE setUnavailable)
    QSharedPointer<bool> unavailable;

    Q_PROPERTY(QJsonValue member_count READ getMemberCount WRITE setMemberCount)
    QSharedPointer<int> member_count;

    Q_PROPERTY(QJsonArray voice_states READ getVoiceStates WRITE setVoiceStates)
    QList<VoiceState> voice_states;

    Q_PROPERTY(QJsonArray members READ getMembers WRITE setMembers)
    QList<GuildMember> members;

    Q_PROPERTY(QJsonArray channels READ getChannels WRITE setChannels)
    QList<Channel> channels;

    Q_PROPERTY(QJsonArray presences READ getPresences WRITE setPresences)
    QList<PresenceUpdate> presences;

    Q_PROPERTY(QJsonValue max_presences READ getMaxPresences WRITE setMaxPresences)
    QSharedPointer<int> max_presences;

    Q_PROPERTY(QJsonValue max_members READ getMaxMembers WRITE setMaxMembers)
    QSharedPointer<int> max_members;

    Q_PROPERTY(QString vanity_url_code READ getVanityUrlCode WRITE setVanityUrlCode)
    QString vanity_url_code;

    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
    QString description;

    Q_PROPERTY(QString banner READ getBanner WRITE setBanner)
    QString banner;

    Q_PROPERTY(int premium_tier READ getPremiumTier WRITE setPremiumTier)
    int premium_tier;

    Q_PROPERTY(QJsonValue premium_subscription_count READ getPremiumSubscriptionCount WRITE setPremiumSubscriptionCount)
    QSharedPointer<int> premium_subscription_count;

    Q_PROPERTY(QString preferred_locale READ getPreferredLocale WRITE setPreferredLocale)
    QString preferred_locale;

    Q_PROPERTY(QString public_updates_channel_id READ getPublicUpdatesChannelId WRITE setPublicUpdatesChannelId)
    QString public_updates_channel_id;

    Q_PROPERTY(QJsonValue max_video_channel_users READ getMaxVideoChannelUsers WRITE setMaxVideoChannelUsers)
    QSharedPointer<int> max_video_channel_users;

    Q_PROPERTY(QJsonValue approximate_member_count READ getApproximateMemberCount WRITE setApproximateMemberCount)
    QSharedPointer<int> approximate_member_count;

    Q_PROPERTY(QJsonValue approximate_presence_count READ getApproximatePresenceCount WRITE setApproximatePresenceCount)
    QSharedPointer<int> approximate_presence_count;

    QString
    getId() {
        return id;
    }

    void
    setId(QString id) {
        this->id = id;
    }

    QString
    getName() {
        return name;
    }

    void
    setName(QString name) {
        this->name = name;
    }

    QString
    getIcon() {
        return icon;
    }

    void
    setIcon(QString icon) {
        this->icon = icon;
    }

    QString
    getSplash() {
        return splash;
    }

    void
    setSplash(QString splash) {
        this->splash = splash;
    }

    QString
    getDiscoverySplash() {
        return discovery_splash;
    }

    void
    setDiscoverySplash(QString discovery_splash) {
        this->discovery_splash = discovery_splash;
    }

    QJsonValue
    getOwner() {
        if (owner) {
            return QJsonValue(*owner);
        } else {
            return QJsonValue();
        }
    }

    void
    setOwner(QJsonValue owner) {
        if (!owner.isNull()) {
            this->owner = QSharedPointer<bool>(new bool(owner.toBool()));
        }
    }

    QString
    getOwnerId() {
        return owner_id;
    }

    void
    setOwnerId(QString owner_id) {
        this->owner_id = owner_id;
    }

    QJsonValue
    getPermissions() {
        if (permissions) {
            return QJsonValue(*permissions);
        } else {
            return QJsonValue();
        }
    }

    void
    setPermissions(QJsonValue permissions) {
        if (!permissions.isNull()) {
            this->permissions = QSharedPointer<int>(new int(permissions.toInt()));
        }
    }

    QString
    getRegion() {
        return region;
    }

    void
    setRegion(QString region) {
        this->region = region;
    }

    QString
    getAfkChannelId() {
        return afk_channel_id;
    }

    void
    setAfkChannelId(QString afk_channel_id) {
        this->afk_channel_id = afk_channel_id;
    }

    int
    getAfkTimeout() {
        return afk_timeout;
    }

    void
    setAfkTimeout(int afk_timeout) {
        this->afk_timeout = afk_timeout;
    }

    QJsonValue
    getEmbedEnabled() {
        if (embed_enabled) {
            return QJsonValue(*embed_enabled);
        } else {
            return QJsonValue();
        }
    }

    void
    setEmbedEnabled(QJsonValue embed_enabled) {
        if (!embed_enabled.isNull()) {
            this->embed_enabled = QSharedPointer<bool>(new bool(embed_enabled.toBool()));
        }
    }

    QString
    getEmbedChannelId() {
        return embed_channel_id;
    }

    void
    setEmbedChannelId(QString embed_channel_id) {
        this->embed_channel_id = embed_channel_id;
    }

    int
    getVerificationLevel() {
        return verification_level;
    }

    void
    setVerificationLevel(int verification_level) {
        this->verification_level = verification_level;
    }

    int
    getDefaultMessageNotifications() {
        return default_message_notifications;
    }

    void
    setDefaultMessageNotifications(int default_message_notifications) {
        this->default_message_notifications = default_message_notifications;
    }

    int
    getExplicitContentFilter() {
        return explicit_content_filter;
    }

    void
    setExplicitContentFilter(int explicit_content_filter) {
        this->explicit_content_filter = explicit_content_filter;
    }

    QJsonArray
    getRoles() {
        QJsonArray roles;
        for (Role role : this->roles) {
            roles.push_back(role.toQJsonObject());
        }
        return roles;
    }

    void
    setRoles(QJsonArray roles) {
        for (QJsonValue jsonValue : roles) {
            Role role;
            JsonUtils::readFromJson(role, jsonValue.toObject());
            this->roles.push_back(role);
        }
    }

    QJsonArray
    getEmojis() {
        QJsonArray emojis;
        for (Emoji emoji : this->emojis) {
            emojis.push_back(emoji.toQJsonObject());
        }
        return emojis;
    }

    void
    setEmojis(QJsonArray emojis) {
        for (QJsonValue jsonValue : emojis) {
            Emoji emoji;
            JsonUtils::readFromJson(emoji, jsonValue.toObject());
            this->emojis.push_back(emoji);
        }
    }

    QJsonArray
    getFeatures() {
        QJsonArray roles;
        for (Role role : this->roles) {
            roles.push_back(role.toQJsonObject());
        }
        return roles;
    }

    void
    setFeatures(QJsonArray features) {
        for (QJsonValue feature : features) {
            this->features.push_back(feature.toString());
        }
    }

    int
    getMfaLevel() {
        return mfa_level;
    }

    void
    setMfaLevel(int mfa_level) {
        this->mfa_level = mfa_level;
    }

    QString
    getApplicationId() {
        return application_id;
    }

    void
    setApplicationId(QString application_id) {
        this->application_id = application_id;
    }

    QJsonValue
    getWidgetEnabled() {
        if (widget_enabled) {
            return QJsonValue(*widget_enabled);
        } else {
            return QJsonValue();
        }
    }

    void
    setWidgetEnabled(QJsonValue widget_enabled) {
        if (!widget_enabled.isNull()) {
            this->widget_enabled = QSharedPointer<bool>(new bool(widget_enabled.toBool()));
        }
    }

    QString
    getWidgetChannelId() {
        return widget_channel_id;
    }

    void
    setWidgetChannelId(QString widget_channel_id) {
        this->widget_channel_id = widget_channel_id;
    }

    QString
    getSystemChannelId() {
        return system_channel_id;
    }

    void
    setSystemChannelId(QString system_channel_id) {
        this->system_channel_id = system_channel_id;
    }

    QJsonValue
    getSystemChannelFlags() {
        if (system_channel_flags) {
            return QJsonValue(*system_channel_flags);
        } else {
            return QJsonValue();
        }
    }

    void
    setSystemChannelFlags(QJsonValue system_channel_flags) {
        if (!system_channel_flags.isNull()) {
            this->system_channel_flags = QSharedPointer<int>(new int(system_channel_flags.toInt()));
        }
    }

    QString
    getRulesChannelId() {
        return rules_channel_id;
    }

    void
    setRulesChannelId(QString rules_channel_id) {
        this->rules_channel_id = rules_channel_id;
    }

    QString
    getJoinedAt() {
        return joined_at;
    }

    void
    setJoinedAt(QString joined_at) {
        this->joined_at = joined_at;
    }

    QJsonValue
    getLarge() {
        if (large) {
            return QJsonValue(*large);
        } else {
            return QJsonValue();
        }
    }

    void
    setLarge(QJsonValue large) {
        if (!large.isNull()) {
            this->large = QSharedPointer<bool>(new bool(large.toBool()));
        }
    }

    QJsonValue
    getUnavailable() {
        if (unavailable) {
            return QJsonValue(*unavailable);
        } else {
            return QJsonValue();
        }
    }

    void
    setUnavailable(QJsonValue unavailable) {
        if (!unavailable.isNull()) {
            this->unavailable = QSharedPointer<bool>(new bool(unavailable.toBool()));
        }
    }

    QJsonValue
    getMemberCount() {
        if (member_count) {
            return QJsonValue(*member_count);
        } else {
            return QJsonValue();
        }
    }

    void
    setMemberCount(QJsonValue member_count) {
        if (!member_count.isNull()) {
            this->member_count = QSharedPointer<int>(new int(member_count.toInt()));
        }
    }

    QJsonArray
    getVoiceStates() {
        QJsonArray voice_states;
        for (VoiceState voiceState : this->voice_states) {
            voice_states.push_back(voiceState.toQJsonObject());
        }
        return voice_states;
    }

    void
    setVoiceStates(QJsonArray voice_states) {
        for (QJsonValue jsonValue : voice_states) {
            VoiceState voiceState;
            JsonUtils::readFromJson(voiceState, jsonValue.toObject());
            this->voice_states.push_back(voiceState);
        }
    }

    QJsonArray
    getMembers() {
        QJsonArray members;
        for (GuildMember guildMember : this->members) {
            members.push_back(guildMember.toQJsonObject());
        }
        return members;
    }

    void
    setMembers(QJsonArray members) {
        for (QJsonValue jsonValue : members) {
            GuildMember guildMember;
            JsonUtils::readFromJson(guildMember, jsonValue.toObject());
            this->members.push_back(guildMember);
        }
    }

    QJsonArray
    getChannels() {
        QJsonArray channels;
        for (Channel channel : this->channels) {
            channels.push_back(channel.toQJsonObject());
        }
        return channels;
    }

    void
    setChannels(QJsonArray channels) {
        for (QJsonValue jsonValue : channels) {
            Channel channel;
            JsonUtils::readFromJson(channel, jsonValue.toObject());
            this->channels.push_back(channel);
        }
    }

    QJsonArray
    getPresences() {
        QJsonArray presences;
        for (PresenceUpdate presenceUpdate : this->presences) {
            presences.push_back(presenceUpdate.toQJsonObject());
        }
        return presences;
    }

    void
    setPresences(QJsonArray presences) {
        for (QJsonValue jsonValue : presences) {
            PresenceUpdate presenceUpdate;
            JsonUtils::readFromJson(presenceUpdate, jsonValue.toObject());
            this->presences.push_back(presenceUpdate);
        }
    }

    QJsonValue
    getMaxPresences() {
        if (max_presences) {
            return QJsonValue(*max_presences);
        } else {
            return QJsonValue();
        }
    }

    void
    setMaxPresences(QJsonValue max_presences) {
        if (!max_presences.isNull()) {
            this->max_presences = QSharedPointer<int>(new int(max_presences.toInt()));
        }
    }

    QJsonValue
    getMaxMembers() {
        if (max_members) {
            return QJsonValue(*max_members);
        } else {
            return QJsonValue();
        }
    }

    void
    setMaxMembers(QJsonValue max_members) {
        if (!max_members.isNull()) {
            this->max_members = QSharedPointer<int>(new int(max_members.toInt()));
        }
    }

    QString
    getVanityUrlCode() {
        return vanity_url_code;
    }

    void
    setVanityUrlCode(QString vanity_url_code) {
        this->vanity_url_code = vanity_url_code;
    }

    QString
    getDescription() {
        return description;
    }

    void
    setDescription(QString description) {
        this->description = description;
    }

    QString
    getBanner() {
        return banner;
    }

    void
    setBanner(QString banner) {
        this->banner = banner;
    }

    int
    getPremiumTier() {
        return premium_tier;
    }

    void
    setPremiumTier(int premium_tier) {
        this->premium_tier = premium_tier;
    }

    QJsonValue
    getPremiumSubscriptionCount() {
        if (premium_subscription_count) {
            return QJsonValue(*premium_subscription_count);
        } else {
            return QJsonValue();
        }
    }

    void
    setPremiumSubscriptionCount(QJsonValue premium_subscription_count) {
        if (!premium_subscription_count.isNull()) {
            this->premium_subscription_count = QSharedPointer<int>(new int(premium_subscription_count.toInt()));
        }
    }

    QString
    getPreferredLocale() {
        return preferred_locale;
    }

    void
    setPreferredLocale(QString preferred_locale) {
        this->preferred_locale = preferred_locale;
    }

    QString
    getPublicUpdatesChannelId() {
        return public_updates_channel_id;
    }

    void
    setPublicUpdatesChannelId(QString public_updates_channel_id) {
        this->public_updates_channel_id = public_updates_channel_id;
    }

    QJsonValue
    getMaxVideoChannelUsers() {
        if (max_video_channel_users) {
            return QJsonValue(*max_video_channel_users);
        } else {
            return QJsonValue();
        }
    }

    void
    setMaxVideoChannelUsers(QJsonValue max_video_channel_users) {
        if (!max_video_channel_users.isNull()) {
            this->premium_subscription_count = QSharedPointer<int>(new int(max_video_channel_users.toInt()));
        }
    }

    QJsonValue
    getApproximateMemberCount() {
        if (approximate_member_count) {
            return QJsonValue(*approximate_member_count);
        } else {
            return QJsonValue();
        }
    }

    void
    setApproximateMemberCount(QJsonValue approximate_member_count) {
        if (!approximate_member_count.isNull()) {
            this->approximate_member_count = QSharedPointer<int>(new int(approximate_member_count.toInt()));
        }
    }

    QJsonValue
    getApproximatePresenceCount() {
        if (approximate_presence_count) {
            return QJsonValue(*approximate_presence_count);
        } else {
            return QJsonValue();
        }
    }

    void
    setApproximatePresenceCount(QJsonValue approximate_presence_count) {
        if (!premium_subscription_count.isNull()) {
            this->approximate_presence_count = QSharedPointer<int>(new int(approximate_presence_count.toInt()));
        }
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }

    enum DEFAULT_NOFICATION_LEVEL {
        ALL_MESSAGES,
        ONLY_MENTIONS
    };

    enum EXPLICIT_CONTENT_FILTER_LEVEL {
        DISABLED,
        MEMBERS_WITHOUT_ROLES,
        ALL_MEMBERS
    };

    enum PREMIUM_TIER_LEVEL {
        TIER_0,
        TIER_1,
        TIER_2,
        TIER_3
    };

    enum VERFICATION_LEVEL {
        NONE,
        LOW,
        MEDIUM,
        HIGH,
        VERY_HIGH
    };


    Q_ENUM(DEFAULT_NOFICATION_LEVEL)
    Q_ENUM(EXPLICIT_CONTENT_FILTER_LEVEL)
    Q_ENUM(PREMIUM_TIER_LEVEL)
    Q_ENUM(VERFICATION_LEVEL)

};


Q_DECLARE_METATYPE(Guild)

#endif // GUILD_H
