#include "activity.h"

#include <jsonutils.h>

#include "activitytimestamps.h"
#include "activityemoji.h"

QString
Activity::getName() {
    return name;
}

void
Activity::setName(QString name) {
    this->name = name;
}

int
Activity::getType() {
    return type;
}

void
Activity::setType(int type) {
    this->type = type;
}

QString
Activity::getUrl() {
    return url;
}

void
Activity::setUrl(QString url) {
    this->url = url;
}

int
Activity::getCreatedAt() {
    return created_at;
}

void
Activity::setCreatedAt(int created_at) {
    this->created_at = created_at;
}

QJsonObject
Activity::getTimestamps() {
    if (timestamps) {
        return timestamps->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Activity::setTimestamps(QJsonObject timestamps) {
    this->timestamps = QSharedPointer<ActivityTimestamps>(new ActivityTimestamps);
    JsonUtils::readFromJson(*this->timestamps, timestamps);
}

QString
Activity::getApplicationId() {
    return application_id;
}

void
Activity::setApplicationId(QString application_id) {
    this->application_id = application_id;
}

QString
Activity::getDetails() {
    return details;
}

void
Activity::setDetails(QString details) {
    this->details = details;
}

QString
Activity::getState() {
    return state;
}

void
Activity::setState(QString state) {
    this->state = state;
}

QJsonObject
Activity::getEmoji() {
    if (emoji) {
        return emoji->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Activity::setEmoji(QJsonObject emoji) {
    this->emoji = QSharedPointer<ActivityEmoji>(new ActivityEmoji);
    JsonUtils::readFromJson(*this->emoji, emoji);
}

QJsonObject
Activity::getParty() {
    if (party) {
        return party->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Activity::setParty(QJsonObject party) {
    this->party = QSharedPointer<ActivityParty>(new ActivityParty);
    JsonUtils::readFromJson(*this->party, party);
}

QJsonObject
Activity::getAssets() {
    if (assets) {
        return assets->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Activity::setAssets(QJsonObject assets) {
    this->assets = QSharedPointer<ActivityAssets>(new ActivityAssets);
    JsonUtils::readFromJson(*this->assets, assets);
}

QJsonObject
Activity::getSecrets() {
    if (secrets) {
        return secrets->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Activity::setSecrets(QJsonObject secrets) {
    this->secrets = QSharedPointer<ActivitySecrets>(new ActivitySecrets);
    JsonUtils::readFromJson(*this->secrets, secrets);
}

QJsonValue
Activity::getInstance() {
    if (instance) {
        return QJsonValue(*instance);
    }
    return QJsonValue();
}

void
Activity::setInstance(QJsonValue instance) {
    if (!instance.isNull()) {
        this->instance = QSharedPointer<bool>(new bool(instance.toBool()));
    }
}

QJsonValue
Activity::getFlags() {
    if (flags) {
        return QJsonValue(*flags);
    }
    return QJsonValue();
}

void
Activity::setFlags(QJsonValue flags) {
    if (!flags.isNull()) {
        this->flags = QSharedPointer<int>(new int(flags.toInt()));
    }
}

void
Activity::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

/*
 * Note Bot can only send fields "name", "type", and "url"
 */
void
Activity::write(QJsonObject &jsonObject) {
    jsonObject[NAME] = name;
    jsonObject[TYPE] = type;

    if (!url.isEmpty()) {
        jsonObject[URL] = url;
    }
}
