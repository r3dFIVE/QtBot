#include "activity.h"

void
Activity::read(const QJsonObject &jsonObject) {
    name = jsonObject[NAME].toString();
    type = jsonObject[TYPE].toInt();

    if (jsonObject.contains(URL)) {
        url = jsonObject[URL].toString();
    }

    created_at = jsonObject[CREATED_AT].toInt(0);

    if (jsonObject.contains(TIMESTAMPS)) {
        timestamps = QSharedPointer<Timestamps>(new Timestamps);
        timestamps->read(jsonObject[TIMESTAMPS].toObject());
    }

    if (jsonObject.contains(APPLICATION_ID)) {
        application_id = jsonObject[APPLICATION_ID].toString();
    }

    if (jsonObject.contains(DETAILS)) {
        details = jsonObject[DETAILS].toString();
    }

    if (jsonObject.contains(STATE)) {
        state = jsonObject[STATE].toString();
    }

    if (jsonObject.contains(EMOJI)) {
        emoji = QSharedPointer<Emoji>(new Emoji);
        emoji->read(jsonObject[EMOJI].toObject());
    }

    if (jsonObject.contains(PARTY)) {
        party = QSharedPointer<Party>(new Party);
        party->read(jsonObject[PARTY].toObject());
    }

    if (jsonObject.contains(ASSETS)) {
        assets = QSharedPointer<Assets>(new Assets);
        assets->read(jsonObject[ASSETS].toObject());
    }

    if (jsonObject.contains(SECRETS)) {
        secrets = QSharedPointer<Secrets>(new Secrets);
        secrets->read(jsonObject[SECRETS].toObject());
    }

    if (jsonObject.contains(INSTANCE)) {
        instance = QSharedPointer<bool>(new bool(jsonObject[INSTANCE].toBool()));
    }

    if (jsonObject.contains(FLAGS)) {
        flags = QSharedPointer<int>(new int(jsonObject[FLAGS].toInt()));
    }
}

/*
 * Note Bot can only send fields "name", "type", and "url"
 */
void
Activity::write(QJsonObject &jsonObject) const {
    jsonObject[NAME] = name;
    jsonObject[TYPE] = type;

    if (!url.isEmpty()) {
        jsonObject[URL] = url;
    }
}
