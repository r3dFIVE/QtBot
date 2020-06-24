#ifndef GUILD_H
#define GUILD_H

#include "jsonserializable.h"

class Emoji;
class PresenceUpdate;

#include "emoji.h"
#include "presenceupdate.h"
#include "channel.h"
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
    QList<QSharedPointer<Emoji> > emojis;

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
    QList<QSharedPointer<PresenceUpdate> > presences;

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

    QString getId();
    void setId(QString id);
    QString getName();
    void setName(QString name);
    QString getIcon();
    void setIcon(QString icon);
    QString getSplash();
    void setSplash(QString splash);
    QString getDiscoverySplash();
    void setDiscoverySplash(QString discovery_splash);
    QJsonValue getOwner();
    void setOwner(QJsonValue owner);
    QString getOwnerId();
    void setOwnerId(QString owner_id);
    QJsonValue getPermissions();
    void setPermissions(QJsonValue permissions);
    QString getRegion();
    void setRegion(QString region);
    QString getAfkChannelId();
    void setAfkChannelId(QString afk_channel_id);
    int getAfkTimeout();
    void setAfkTimeout(int afk_timeout);
    QJsonValue getEmbedEnabled();
    void setEmbedEnabled(QJsonValue embed_enabled);
    QString getEmbedChannelId();
    void setEmbedChannelId(QString embed_channel_id);
    int getVerificationLevel();
    void setVerificationLevel(int verification_level);
    int getDefaultMessageNotifications();
    void setDefaultMessageNotifications(int default_message_notifications);
    int getExplicitContentFilter();
    void setExplicitContentFilter(int explicit_content_filter);
    QJsonArray getRoles();
    void setRoles(QJsonArray roles) ;
    QJsonArray getEmojis();
    void setEmojis(QJsonArray emojis);
    QJsonArray getFeatures();
    void setFeatures(QJsonArray features);
    int getMfaLevel();
    void setMfaLevel(int mfa_level);
    QString getApplicationId() ;
    void setApplicationId(QString application_id);
    QJsonValue getWidgetEnabled();
    void setWidgetEnabled(QJsonValue widget_enabled);
    QString getWidgetChannelId();
    void setWidgetChannelId(QString widget_channel_id);
    QString getSystemChannelId();
    void setSystemChannelId(QString system_channel_id);
    QJsonValue getSystemChannelFlags();
    void setSystemChannelFlags(QJsonValue system_channel_flags);
    QString getRulesChannelId();
    void setRulesChannelId(QString rules_channel_id);
    QString getJoinedAt();
    void setJoinedAt(QString joined_at);
    QJsonValue getLarge();
    void setLarge(QJsonValue large);
    QJsonValue getUnavailable();
    void setUnavailable(QJsonValue unavailable);
    QJsonValue getMemberCount();
    void setMemberCount(QJsonValue member_count);
    QJsonArray getVoiceStates();
    void setVoiceStates(QJsonArray voice_states);
    QJsonArray getMembers();
    void setMembers(QJsonArray members);
    QJsonArray getChannels();
    void setChannels(QJsonArray channels);
    QJsonArray getPresences();
    void setPresences(QJsonArray presences);
    QJsonValue getMaxPresences();
    void setMaxPresences(QJsonValue max_presences);
    QJsonValue getMaxMembers();
    void setMaxMembers(QJsonValue max_members);
    QString getVanityUrlCode();
    void setVanityUrlCode(QString vanity_url_code);
    QString getDescription();
    void setDescription(QString description);
    QString getBanner();
    void setBanner(QString banner);
    int getPremiumTier();
    void setPremiumTier(int premium_tier);
    QJsonValue getPremiumSubscriptionCount();
    void setPremiumSubscriptionCount(QJsonValue premium_subscription_count);
    QString getPreferredLocale();
    void setPreferredLocale(QString preferred_locale);
    QString getPublicUpdatesChannelId();
    void setPublicUpdatesChannelId(QString public_updates_channel_id);
    QJsonValue getMaxVideoChannelUsers();
    void setMaxVideoChannelUsers(QJsonValue max_video_channel_users);
    QJsonValue getApproximateMemberCount();
    void setApproximateMemberCount(QJsonValue approximate_member_count);
    QJsonValue getApproximatePresenceCount();
    void setApproximatePresenceCount(QJsonValue approximate_presence_count);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

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
