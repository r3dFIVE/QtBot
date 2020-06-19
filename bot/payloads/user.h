#ifndef USER_H
#define USER_H

#include "jsonserializeable.h"


class User : public JsonSerializeable
{
public:
    const QString ID = "id";
    const QString USERNAME = "username";
    const QString DISCRIMINATOR = "discriminator";
    const QString AVATAR = "avatar";
    const QString BOT = "bot";
    const QString SYSTEM = "system";
    const QString MFA_ENABLED = "mfa_enabled";
    const QString LOCALE = "locale";
    const QString VERIFIED = "verified";
    const QString EMAIL = "email";
    const QString FLAGS = "flags";
    const QString PREMIUM_TYPE = "premium_type";
    const QString PUBLIC_FLAGS = "public_flags";

    QString id;
    QString username;
    QString discriminator;
    QString avatar;
    QSharedPointer<bool> bot;
    QSharedPointer<bool> system;
    QSharedPointer<bool> mfaEnabled;
    QString locale;
    QSharedPointer<bool> verified;
    QString email;
    QSharedPointer<int> flags;
    QSharedPointer<int> premiumType;
    QSharedPointer<int> publicFlags;


    void read(const QJsonObject &jsonObject) override {
        id = jsonObject[ID].toString();
        username = jsonObject[USERNAME].toString();
        discriminator = jsonObject[DISCRIMINATOR].toString();
        avatar = jsonObject[AVATAR].toString();

        if (jsonObject.contains(BOT)) {
            bot = QSharedPointer<bool>(new bool(jsonObject[BOT].toBool()));
        }

        if (jsonObject.contains(SYSTEM)) {
            system = QSharedPointer<bool>(new bool(jsonObject[SYSTEM].toBool()));
        }

        if (jsonObject.contains(MFA_ENABLED)) {
            mfaEnabled = QSharedPointer<bool>(new bool(jsonObject[MFA_ENABLED].toBool()));
        }

        if (jsonObject.contains(LOCALE)) {
            locale = jsonObject[LOCALE].toString();
        }

        if (jsonObject.contains(VERIFIED)) {
            verified = QSharedPointer<bool>(new bool(jsonObject[VERIFIED].toBool()));
        }

        if (jsonObject.contains(EMAIL)) {
            email = jsonObject[EMAIL].toString();
        }

        if (jsonObject.contains(FLAGS)) {
            flags = QSharedPointer<int>(new int(jsonObject[FLAGS].toInt()));
        }

        if (jsonObject.contains(PREMIUM_TYPE)) {
            premiumType = QSharedPointer<int>(new int(jsonObject[PREMIUM_TYPE].toInt()));
        }

        if (jsonObject.contains(PUBLIC_FLAGS)) {
            publicFlags = QSharedPointer<int>(new int(jsonObject[PUBLIC_FLAGS].toInt()));
        }
    }

    void write(QJsonObject &jsonObject) override {
        jsonObject[ID] = id;
        jsonObject[USERNAME] = username;
        jsonObject[DISCRIMINATOR] = discriminator;
        jsonObject[AVATAR] = avatar;

        if (bot != nullptr) {
            jsonObject[BOT] = *bot;
        }

        if (system != nullptr) {
            jsonObject[SYSTEM] = *system;
        }

        if (mfaEnabled != nullptr) {
            jsonObject[MFA_ENABLED] = *mfaEnabled;
        }

        if (locale != "") {
            jsonObject[LOCALE] = locale;
        }

        if (verified != nullptr) {
            jsonObject[VERIFIED] = *verified;
        }

        if (email != "") {
            jsonObject[EMAIL] = email;
        }

        if (flags != nullptr) {
            jsonObject[FLAGS] = *flags;
        }

        if (premiumType != nullptr) {
            jsonObject[PREMIUM_TYPE] = *premiumType;
        }

        if (publicFlags != nullptr) {
            jsonObject[PUBLIC_FLAGS] = *publicFlags;
        }
    }
};

#endif // USER_H
