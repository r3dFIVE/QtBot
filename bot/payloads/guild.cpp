#include "guild.h"


const QString Guild::ID = "id";
const QString Guild::NAME = "name";
const QString Guild::ICON = "icon";
const QString Guild::SPLASH = "splash";
const QString Guild::DISCOVERY_SPLASH = "discovery_splash";
const QString Guild::OWNER = "owner";
const QString Guild::OWNER_ID = "owner_id";
const QString Guild::PERMISSIONS = "permission";
const QString Guild::REGION = "region";
const QString Guild::AFK_CHANNEL_ID = "afk_channel_id";
const QString Guild::AFK_TIMEOUT = "afk_timeout";
const QString Guild::EMBED_ENABLED = "embed_enabled";
const QString Guild::EMBED_CHANNEL_ID = "embed_channel_id";
const QString Guild::VERIFICATION_LEVEL = "verification_level";
const QString Guild::DEFAULT_MESSAGE_NOTIFICATIONS = "default_message_notifications";
const QString Guild::EXPLICIT_CONTENT_FILTER = "explicit_content_filter";
const QString Guild::ROLES = "roles";
const QString Guild::EMOJIS = "emojis";
const QString Guild::FEATURES = "features";
const QString Guild::MFA_LEVEL = "mfa_level";
const QString Guild::APPLICATION_ID = "application_id";
const QString Guild::WIDGET_ENABLED = "widget_enabled";
const QString Guild::WIDGET_CHANNEL_ID = "widget_channel_id";
const QString Guild::SYSTEM_CHANNEL_ID = "system_channel_id";
const QString Guild::SYSTEM_CHANNEL_FLAGS = "system_channel_flags";
const QString Guild::RULES_CHANNEL_ID = "rules_channel_id";
const QString Guild::JOINED_AT = "joined_at";
const QString Guild::LARGE = "large";
const QString Guild::UNAVAILABLE = "unavailable";
const QString Guild::MEMBER_COUNT = "member_count";
const QString Guild::VOICE_STATES = "voice_states";
const QString Guild::MEMBERS = "members";
const QString Guild::CHANNELS = "channels";
const QString Guild::PRESENCES = "presences";
const QString Guild::MAX_PRESENCES = "max_presences";
const QString Guild::MAX_MEMBERS = "max_members";
const QString Guild::VANITY_URL_CODE = "vanity_url_code";
const QString Guild::DESCRIPTION = "description";
const QString Guild::BANNER = "banner";
const QString Guild::PREMIUM_TIER = "premium_tier";
const QString Guild::PREMIUM_SUBSCRIPTION_COUNT = "premium_subscription_count";
const QString Guild::PREFERRED_LOCALE = "preferred_locale";
const QString Guild::PUBLIC_UPDATES_CHANNEL_ID = "public_update_channel_id";
const QString Guild::MAX_VIDEO_CHANNEL_USERS = "max_video_channel_users";
const QString Guild::APPROXIMATE_MEMBER_COUNT = "approximate_member_count";
const QString Guild::APPROXIMATE_PRESENCE_COUNT = "approximate_user_count";

QJsonValue
Guild::getId() const {
    return _jsonObject[ID];
}

void
Guild::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
Guild::getName() const {
    return _jsonObject[NAME];
}

void
Guild::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonValue
Guild::getIcon() const {
    return _jsonObject[ICON];
}

void
Guild::setIcon(const QJsonValue &icon) {
    _jsonObject[ICON] = icon;
}

QJsonValue
Guild::getSplash() const {
    return _jsonObject[SPLASH];
}

void
Guild::setSplash(const QJsonValue &splash) {
    _jsonObject[SPLASH] = splash;
}

QJsonValue
Guild::getDiscoverySplash() const {
    return _jsonObject[DISCOVERY_SPLASH];
}

void
Guild::setDiscoverySplash(const QJsonValue &discoverySplash) {
    _jsonObject[DISCOVERY_SPLASH] = discoverySplash;
}

QJsonValue
Guild::getOwner() const {
    return _jsonObject[OWNER];
}

void
Guild::setOwner(const QJsonValue &owner) {
    _jsonObject[OWNER] = owner;
}

QJsonValue
Guild::getOwnerId() const {
    return _jsonObject[OWNER_ID];
}

void
Guild::setOwnerId(const QJsonValue &ownerId) {
    _jsonObject[OWNER_ID] = ownerId;
}

QJsonValue
Guild::getPermissions() const {
    return _jsonObject[PERMISSIONS];
}

void
Guild::setPermissions(const QJsonValue &permissions) {
    _jsonObject[PERMISSIONS] = permissions;
}

QJsonValue
Guild::getRegion() const {
    return _jsonObject[REGION];
}

void
Guild::setRegion(const QJsonValue &region) {
    _jsonObject[REGION] = region;
}

QJsonValue
Guild::getAfkChannelId() const {
    return _jsonObject[AFK_CHANNEL_ID];
}

void
Guild::setAfkChannelId(const QJsonValue &afkChannelId) {
    _jsonObject[AFK_CHANNEL_ID] = afkChannelId;
}

QJsonValue
Guild::getAfkTimeout() const {
    return _jsonObject[AFK_TIMEOUT];
}

void
Guild::setAfkTimeout(const QJsonValue &afkTimeout) {
    _jsonObject[AFK_TIMEOUT] = afkTimeout;
}

QJsonValue
Guild::getEmbedEnabled() const {
    return _jsonObject[EMBED_ENABLED];
}

void
Guild::setEmbedEnabled(const QJsonValue &embedEnabled) {
    _jsonObject[EMBED_ENABLED] = embedEnabled;
}

QJsonValue
Guild::getEmbedChannelId() const {
    return _jsonObject[EMBED_CHANNEL_ID];
}

void
Guild::setEmbedChannelId(const QJsonValue &embedChannelId) {
    _jsonObject[EMBED_CHANNEL_ID]= embedChannelId;
}

QJsonValue
Guild::getVerificationLevel() const {
    return _jsonObject[VERIFICATION_LEVEL];
}

void
Guild::setVerificationLevel(const QJsonValue &verificationLevel) {
    _jsonObject[VERIFICATION_LEVEL] = verificationLevel;
}

QJsonValue
Guild::getDefaultMessageNotifications() const {
    return _jsonObject[DEFAULT_MESSAGE_NOTIFICATIONS];
}

void
Guild::setDefaultMessageNotifications(const QJsonValue &defaultMessageNotifications) {
    _jsonObject[DEFAULT_MESSAGE_NOTIFICATIONS] = defaultMessageNotifications;
}

QJsonValue
Guild::getExplicitContentFilter() const {
    return _jsonObject[EXPLICIT_CONTENT_FILTER];
}

void
Guild::setExplicitContentFilter(const QJsonValue &explicitContentFilter) {
    _jsonObject[EXPLICIT_CONTENT_FILTER] = explicitContentFilter;
}

QJsonArray
Guild::getRoles() const {
    return _jsonObject[ROLES].toArray();
}

void
Guild::setRoles(const QJsonArray &roles) {
    _jsonObject[ROLES] = roles;
}

QJsonArray
Guild::getEmojis() const {
    return _jsonObject[EMOJIS].toArray();
}

void
Guild::setEmojis(const QJsonArray &emojis) {
    _jsonObject[EMOJIS] = emojis;
}

QJsonArray
Guild::getFeatures() const {
    return _jsonObject[FEATURES].toArray();
}

void
Guild::setFeatures(const QJsonArray &features) {
    _jsonObject[FEATURES] = features;
}

QJsonValue
Guild::getMfaLevel() const {
    return _jsonObject[MFA_LEVEL];
}

void
Guild::setMfaLevel(const QJsonValue &mfaLevel) {
    _jsonObject[MFA_LEVEL] = mfaLevel;
}

QJsonValue
Guild::getApplicationId() const {
    return _jsonObject[APPLICATION_ID];
}

void
Guild::setApplicationId(const QJsonValue &applicationId) {
    _jsonObject[APPLICATION_ID] = applicationId;
}

QJsonValue
Guild::getWidgetEnabled() const {
    return _jsonObject[WIDGET_ENABLED];
}

void
Guild::setWidgetEnabled(const QJsonValue &widgetEnabled) {
    _jsonObject[WIDGET_ENABLED] = widgetEnabled;
}

QJsonValue
Guild::getWidgetChannelId() const {
    return _jsonObject[WIDGET_CHANNEL_ID];
}

void
Guild::setWidgetChannelId(const QJsonValue &widgetChannelId) {
    _jsonObject[WIDGET_CHANNEL_ID] = widgetChannelId;
}

QJsonValue
Guild::getSystemChannelId() const {
    return _jsonObject[PERMISSIONS];
}

void
Guild::setSystemChannelId(const QJsonValue &systemChannelId) {
    _jsonObject[SYSTEM_CHANNEL_ID] = systemChannelId;
}

QJsonValue
Guild::getSystemChannelFlags() const {
    return _jsonObject[SYSTEM_CHANNEL_FLAGS];
}

void
Guild::setSystemChannelFlags(const QJsonValue &systemChannelFlags) {
    _jsonObject[SYSTEM_CHANNEL_FLAGS] = systemChannelFlags;
}

QJsonValue
Guild::getRulesChannelId() const {
    return _jsonObject[RULES_CHANNEL_ID];
}

void
Guild::setRulesChannelId(const QJsonValue &rulesChannelId) {
    _jsonObject[RULES_CHANNEL_ID] = rulesChannelId;
}

QJsonValue
Guild::getJoinedAt() const {
    return _jsonObject[JOINED_AT];
}

void
Guild::setJoinedAt(const QJsonValue &joinedAt) {
    _jsonObject[JOINED_AT] = joinedAt;
}

QJsonValue
Guild::getLarge() const {
    return _jsonObject[LARGE];
}

void
Guild::setLarge(const QJsonValue &large) {
    _jsonObject[LARGE] = large;
}

QJsonValue
Guild::getUnavailable() const {
    return _jsonObject[UNAVAILABLE];
}

void
Guild::setUnavailable(const QJsonValue &unavailable) {
    _jsonObject[UNAVAILABLE] = unavailable;
}

QJsonValue
Guild::getMemberCount() const {
    return _jsonObject[MEMBER_COUNT];
}

void
Guild::setMemberCount(const QJsonValue &memberCount) {
    _jsonObject[MEMBER_COUNT] = memberCount;
}

QJsonArray
Guild::getVoiceStates() const {
    return _jsonObject[VOICE_STATES].toArray();
}

void
Guild::setVoiceStates(const QJsonArray &voiceStates) {
    _jsonObject[VOICE_STATES] = voiceStates;
}

QJsonArray
Guild::getMembers() const {
    return _jsonObject[MEMBERS].toArray();
}

void
Guild::setMembers(const QJsonArray &members) {
    _jsonObject[MEMBERS] = members;
}

QJsonArray
Guild::getChannels() const {
    return _jsonObject[CHANNELS].toArray();
}

void
Guild::setChannels(const QJsonArray &channels) {
    _jsonObject[CHANNELS] = channels;
}

QJsonArray
Guild::getPresences() const {
    return _jsonObject[PRESENCES].toArray();
}

void
Guild::setPresences(const QJsonArray &presences) {
    _jsonObject[PRESENCES] = presences;
}

QJsonValue
Guild::getMaxPresences() const {
    return _jsonObject[MAX_PRESENCES];
}

void
Guild::setMaxPresences(const QJsonValue &maxPresences) {
    _jsonObject[MAX_PRESENCES] = maxPresences;
}

QJsonValue
Guild::getMaxMembers() const {
    return _jsonObject[MAX_MEMBERS];
}

void
Guild::setMaxMembers(const QJsonValue &maxMembers) {
    _jsonObject[MAX_MEMBERS] = maxMembers;
}

QJsonValue
Guild::getVanityUrlCode() const {
    return _jsonObject[VANITY_URL_CODE];
}

void
Guild::setVanityUrlCode(const QJsonValue &vanityUrlCode) {
    _jsonObject[VANITY_URL_CODE] = vanityUrlCode;
}

QJsonValue
Guild::getDescription() const {
    return _jsonObject[DESCRIPTION];
}

void
Guild::setDescription(const QJsonValue &description) {
    _jsonObject[DESCRIPTION] = description;
}

QJsonValue
Guild::getBanner() const {
    return _jsonObject[BANNER];
}

void
Guild::setBanner(const QJsonValue &banner) {
    _jsonObject[BANNER] = banner;
}

QJsonValue
Guild::getPremiumTier() const {
    return _jsonObject[PREMIUM_TIER];
}

void
Guild::setPremiumTier(const QJsonValue &premiumTier) {
    _jsonObject[PREMIUM_TIER] = premiumTier;
}

QJsonValue
Guild::getPremiumSubscriptionCount() const {
    return _jsonObject[PREMIUM_SUBSCRIPTION_COUNT];
}

void
Guild::setPremiumSubscriptionCount(const QJsonValue &premiumSubscriptionCount) {
    _jsonObject[PREMIUM_SUBSCRIPTION_COUNT] = premiumSubscriptionCount;
}

QJsonValue
Guild::getPreferredLocale() const {
    return _jsonObject[PREFERRED_LOCALE];
}

void
Guild::setPreferredLocale(const QJsonValue &preferredLocale) {
    _jsonObject[PREFERRED_LOCALE] = preferredLocale;
}

QJsonValue
Guild::getPublicUpdatesChannelId() const {
    return _jsonObject[PUBLIC_UPDATES_CHANNEL_ID];
}

void
Guild::setPublicUpdatesChannelId(const QJsonValue &publicUpdatesChannelId) {
    _jsonObject[PUBLIC_UPDATES_CHANNEL_ID] = publicUpdatesChannelId;
}

QJsonValue
Guild::getMaxVideoChannelUsers() const {
    return _jsonObject[MAX_VIDEO_CHANNEL_USERS];
}

void
Guild::setMaxVideoChannelUsers(const QJsonValue &maxVideoChannelUsers) {
    _jsonObject[MAX_VIDEO_CHANNEL_USERS] = maxVideoChannelUsers;
}

QJsonValue
Guild::getApproximateMemberCount() const {
    return _jsonObject[APPROXIMATE_MEMBER_COUNT];
}

void
Guild::setApproximateMemberCount(const QJsonValue &approximateMemberCount) {
    _jsonObject[APPROXIMATE_MEMBER_COUNT] = approximateMemberCount;
}

QJsonValue
Guild::getApproximatePresenceCount() const {
    return _jsonObject[APPROXIMATE_PRESENCE_COUNT];
}

void
Guild::setApproximatePresenceCount(const QJsonValue &approximatePresenceCount) {
    _jsonObject[APPROXIMATE_PRESENCE_COUNT] = approximatePresenceCount;
}
