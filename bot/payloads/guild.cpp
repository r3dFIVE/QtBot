#include "guild.h"

#include "util/serializationutils.h"

class Emoji;
class PresenceUpdate;

QString
Guild::getId() {
    return id;
}

void
Guild::setId(QString id) {
    this->id = id;
}

QString
Guild::getName() {
    return name;
}

void
Guild::setName(QString name) {
    this->name = name;
}

QString
Guild::getIcon() {
    return icon;
}

void
Guild::setIcon(QString icon) {
    this->icon = icon;
}

QString
Guild::getSplash() {
    return splash;
}

void
Guild::setSplash(QString splash) {
    this->splash = splash;
}

QString
Guild::getDiscoverySplash() {
    return discovery_splash;
}

void
Guild::setDiscoverySplash(QString discovery_splash) {
    this->discovery_splash = discovery_splash;
}

QJsonValue
Guild::getOwner() {
    if (owner) {
        return QJsonValue(*owner);
    } else {
        return QJsonValue();
    }
}

void
Guild::setOwner(QJsonValue owner) {
    if (!owner.isNull()) {
        this->owner = QSharedPointer<bool>(new bool(owner.toBool()));
    }
}

QString
Guild::getOwnerId() {
    return owner_id;
}

void
Guild::setOwnerId(QString owner_id) {
    this->owner_id = owner_id;
}

QJsonValue
Guild::getPermissions() {
    if (permissions) {
        return QJsonValue(*permissions);
    } else {
        return QJsonValue();
    }
}

void
Guild::setPermissions(QJsonValue permissions) {
    if (!permissions.isNull()) {
        this->permissions = QSharedPointer<int>(new int(permissions.toInt()));
    }
}

QString
Guild::getRegion() {
    return region;
}

void
Guild::setRegion(QString region) {
    this->region = region;
}

QString
Guild::getAfkChannelId() {
    return afk_channel_id;
}

void
Guild::setAfkChannelId(QString afk_channel_id) {
    this->afk_channel_id = afk_channel_id;
}

int
Guild::getAfkTimeout() {
    return afk_timeout;
}

void
Guild::setAfkTimeout(int afk_timeout) {
    this->afk_timeout = afk_timeout;
}

QJsonValue
Guild::getEmbedEnabled() {
    if (embed_enabled) {
        return QJsonValue(*embed_enabled);
    } else {
        return QJsonValue();
    }
}

void
Guild::setEmbedEnabled(QJsonValue embed_enabled) {
    if (!embed_enabled.isNull()) {
        this->embed_enabled = QSharedPointer<bool>(new bool(embed_enabled.toBool()));
    }
}

QString
Guild::getEmbedChannelId() {
    return embed_channel_id;
}

void
Guild::setEmbedChannelId(QString embed_channel_id) {
    this->embed_channel_id = embed_channel_id;
}

int
Guild::getVerificationLevel() {
    return verification_level;
}

void
Guild::setVerificationLevel(int verification_level) {
    this->verification_level = verification_level;
}

int
Guild::getDefaultMessageNotifications() {
    return default_message_notifications;
}

void
Guild::setDefaultMessageNotifications(int default_message_notifications) {
    this->default_message_notifications = default_message_notifications;
}

int
Guild::getExplicitContentFilter() {
    return explicit_content_filter;
}

void
Guild::setExplicitContentFilter(int explicit_content_filter) {
    this->explicit_content_filter = explicit_content_filter;
}

QJsonArray
Guild::getRoles() {
    QJsonArray roles;
    for (Role role : this->roles) {
        roles.push_back(role.toQJsonObject());
    }
    return roles;
}

void
Guild::setRoles(QJsonArray roles) {
    for (QJsonValue jsonValue : roles) {
        Role role;
        SerializationUtils::readFromJson(role, jsonValue.toObject());
        this->roles.push_back(role);
    }
}

QJsonArray
Guild::getEmojis() {
    QJsonArray emojis;
    for (QSharedPointer<Emoji> emoji : this->emojis) {
        emojis.push_back(emoji->toQJsonObject());
    }
    return emojis;
}

void
Guild::setEmojis(QJsonArray emojis) {
    for (QJsonValue jsonValue : emojis) {
        QSharedPointer<Emoji> emoji = QSharedPointer<Emoji>(new Emoji);
        SerializationUtils::readFromJson(*emoji, jsonValue.toObject());
        this->emojis.push_back(emoji);
    }
}

QJsonArray
Guild::getFeatures() {
    QJsonArray roles;
    for (Role role : this->roles) {
        roles.push_back(role.toQJsonObject());
    }
    return roles;
}

void
Guild::setFeatures(QJsonArray features) {
    for (QJsonValue feature : features) {
        this->features.push_back(feature.toString());
    }
}

int
Guild::getMfaLevel() {
    return mfa_level;
}

void
Guild::setMfaLevel(int mfa_level) {
    this->mfa_level = mfa_level;
}

QString
Guild::getApplicationId() {
    return application_id;
}

void
Guild::setApplicationId(QString application_id) {
    this->application_id = application_id;
}

QJsonValue
Guild::getWidgetEnabled() {
    if (widget_enabled) {
        return QJsonValue(*widget_enabled);
    } else {
        return QJsonValue();
    }
}

void
Guild::setWidgetEnabled(QJsonValue widget_enabled) {
    if (!widget_enabled.isNull()) {
        this->widget_enabled = QSharedPointer<bool>(new bool(widget_enabled.toBool()));
    }
}

QString
Guild::getWidgetChannelId() {
    return widget_channel_id;
}

void
Guild::setWidgetChannelId(QString widget_channel_id) {
    this->widget_channel_id = widget_channel_id;
}

QString
Guild::getSystemChannelId() {
    return system_channel_id;
}

void
Guild::setSystemChannelId(QString system_channel_id) {
    this->system_channel_id = system_channel_id;
}

QJsonValue
Guild::getSystemChannelFlags() {
    if (system_channel_flags) {
        return QJsonValue(*system_channel_flags);
    } else {
        return QJsonValue();
    }
}

void
Guild::setSystemChannelFlags(QJsonValue system_channel_flags) {
    if (!system_channel_flags.isNull()) {
        this->system_channel_flags = QSharedPointer<int>(new int(system_channel_flags.toInt()));
    }
}

QString
Guild::getRulesChannelId() {
    return rules_channel_id;
}

void
Guild::setRulesChannelId(QString rules_channel_id) {
    this->rules_channel_id = rules_channel_id;
}

QString
Guild::getJoinedAt() {
    return joined_at;
}

void
Guild::setJoinedAt(QString joined_at) {
    this->joined_at = joined_at;
}

QJsonValue
Guild::getLarge() {
    if (large) {
        return QJsonValue(*large);
    } else {
        return QJsonValue();
    }
}

void
Guild::setLarge(QJsonValue large) {
    if (!large.isNull()) {
        this->large = QSharedPointer<bool>(new bool(large.toBool()));
    }
}

QJsonValue
Guild::getUnavailable() {
    if (unavailable) {
        return QJsonValue(*unavailable);
    } else {
        return QJsonValue();
    }
}

void
Guild::setUnavailable(QJsonValue unavailable) {
    if (!unavailable.isNull()) {
        this->unavailable = QSharedPointer<bool>(new bool(unavailable.toBool()));
    }
}

QJsonValue
Guild::getMemberCount() {
    if (member_count) {
        return QJsonValue(*member_count);
    } else {
        return QJsonValue();
    }
}

void
Guild::setMemberCount(QJsonValue member_count) {
    if (!member_count.isNull()) {
        this->member_count = QSharedPointer<int>(new int(member_count.toInt()));
    }
}

QJsonArray
Guild::getVoiceStates() {
    QJsonArray voice_states;
    for (VoiceState voiceState : this->voice_states) {
        voice_states.push_back(voiceState.toQJsonObject());
    }
    return voice_states;
}

void
Guild::setVoiceStates(QJsonArray voice_states) {
    for (QJsonValue jsonValue : voice_states) {
        VoiceState voiceState;
        SerializationUtils::readFromJson(voiceState, jsonValue.toObject());
        this->voice_states.push_back(voiceState);
    }
}

QJsonArray
Guild::getMembers() {
    QJsonArray members;
    for (GuildMember guildMember : this->members) {
        members.push_back(guildMember.toQJsonObject());
    }
    return members;
}

void
Guild::setMembers(QJsonArray members) {
    for (QJsonValue jsonValue : members) {
        GuildMember guildMember;
        SerializationUtils::readFromJson(guildMember, jsonValue.toObject());
        this->members.push_back(guildMember);
    }
}

QJsonArray
Guild::getChannels() {
    QJsonArray channels;
    for (Channel channel : this->channels) {
        channels.push_back(channel.toQJsonObject());
    }
    return channels;
}

void
Guild::setChannels(QJsonArray channels) {
    for (QJsonValue jsonValue : channels) {
        Channel channel;
        SerializationUtils::readFromJson(channel, jsonValue.toObject());
        this->channels.push_back(channel);
    }
}

QJsonArray
Guild::getPresences() {
    QJsonArray presences;
    for (QSharedPointer<PresenceUpdate> presenceUpdate : this->presences) {
        presences.push_back(presenceUpdate->toQJsonObject());
    }
    return presences;
}

void
Guild::setPresences(QJsonArray presences) {
    for (QJsonValue jsonValue : presences) {
        QSharedPointer<PresenceUpdate> presenceUpdate = QSharedPointer<PresenceUpdate>();
        SerializationUtils::readFromJson(*presenceUpdate, jsonValue.toObject());
        this->presences.push_back(presenceUpdate);
    }
}

QJsonValue
Guild::getMaxPresences() {
    if (max_presences) {
        return QJsonValue(*max_presences);
    } else {
        return QJsonValue();
    }
}

void
Guild::setMaxPresences(QJsonValue max_presences) {
    if (!max_presences.isNull()) {
        this->max_presences = QSharedPointer<int>(new int(max_presences.toInt()));
    }
}

QJsonValue
Guild::getMaxMembers() {
    if (max_members) {
        return QJsonValue(*max_members);
    } else {
        return QJsonValue();
    }
}

void
Guild::setMaxMembers(QJsonValue max_members) {
    if (!max_members.isNull()) {
        this->max_members = QSharedPointer<int>(new int(max_members.toInt()));
    }
}

QString
Guild::getVanityUrlCode() {
    return vanity_url_code;
}

void
Guild::setVanityUrlCode(QString vanity_url_code) {
    this->vanity_url_code = vanity_url_code;
}

QString
Guild::getDescription() {
    return description;
}

void
Guild::setDescription(QString description) {
    this->description = description;
}

QString
Guild::getBanner() {
    return banner;
}

void
Guild::setBanner(QString banner) {
    this->banner = banner;
}

int
Guild::getPremiumTier() {
    return premium_tier;
}

void
Guild::setPremiumTier(int premium_tier) {
    this->premium_tier = premium_tier;
}

QJsonValue
Guild::getPremiumSubscriptionCount() {
    if (premium_subscription_count) {
        return QJsonValue(*premium_subscription_count);
    } else {
        return QJsonValue();
    }
}

void
Guild::setPremiumSubscriptionCount(QJsonValue premium_subscription_count) {
    if (!premium_subscription_count.isNull()) {
        this->premium_subscription_count = QSharedPointer<int>(new int(premium_subscription_count.toInt()));
    }
}

QString
Guild::getPreferredLocale() {
    return preferred_locale;
}

void
Guild::setPreferredLocale(QString preferred_locale) {
    this->preferred_locale = preferred_locale;
}

QString
Guild::getPublicUpdatesChannelId() {
    return public_updates_channel_id;
}

void
Guild::setPublicUpdatesChannelId(QString public_updates_channel_id) {
    this->public_updates_channel_id = public_updates_channel_id;
}

QJsonValue
Guild::getMaxVideoChannelUsers() {
    if (max_video_channel_users) {
        return QJsonValue(*max_video_channel_users);
    } else {
        return QJsonValue();
    }
}

void
Guild::setMaxVideoChannelUsers(QJsonValue max_video_channel_users) {
    if (!max_video_channel_users.isNull()) {
        this->premium_subscription_count = QSharedPointer<int>(new int(max_video_channel_users.toInt()));
    }
}

QJsonValue
Guild::getApproximateMemberCount() {
    if (approximate_member_count) {
        return QJsonValue(*approximate_member_count);
    } else {
        return QJsonValue();
    }
}

void
Guild::setApproximateMemberCount(QJsonValue approximate_member_count) {
    if (!approximate_member_count.isNull()) {
        this->approximate_member_count = QSharedPointer<int>(new int(approximate_member_count.toInt()));
    }
}

QJsonValue
Guild::getApproximatePresenceCount() {
    if (approximate_presence_count) {
        return QJsonValue(*approximate_presence_count);
    } else {
        return QJsonValue();
    }
}

void
Guild::setApproximatePresenceCount(QJsonValue approximate_presence_count) {
    if (!premium_subscription_count.isNull()) {
        this->approximate_presence_count = QSharedPointer<int>(new int(approximate_presence_count.toInt()));
    }
}

void
Guild::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
Guild::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
