#ifndef USER_H
#define USER_H

#include "jsonserializable.h"

class User : public JsonSerializable
{
    Q_OBJECT

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

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QString username READ getUsername WRITE setUsername)
    QString username;

    Q_PROPERTY(QString discriminator READ getDiscriminator WRITE setDiscriminator)
    QString discriminator;

    Q_PROPERTY(QString avatar READ getAvatar WRITE setAvatar)
    QString avatar;

    Q_PROPERTY(QJsonValue bot READ getBot WRITE setBot)
    QSharedPointer<bool> bot;

    Q_PROPERTY(QJsonValue system READ getSystem WRITE setSystem)
    QSharedPointer<bool> system;

    Q_PROPERTY(QJsonValue mfa_enabled READ getMfaEnabled WRITE setMfaEnabled)
    QSharedPointer<bool> mfa_enabled;

    Q_PROPERTY(QString locale READ getLocale WRITE setLocale)
    QString locale;

    Q_PROPERTY(QJsonValue verified READ getVerified WRITE setVerified)
    QSharedPointer<bool> verified;

    Q_PROPERTY(QString email READ getEmail WRITE setEmail)
    QString email;

    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
    QSharedPointer<int> flags;

    Q_PROPERTY(QJsonValue premium_type READ getPremiumType WRITE setPremiumType)
    QSharedPointer<int> premium_type;

    Q_PROPERTY(QJsonValue public_flags READ getPublicFlags WRITE setPublicFlags)
    QSharedPointer<int> public_flags;

    QString getId();
    void setId(QString id);
    QString getUsername();
    void setUsername(QString username);
    QString getDiscriminator();
    void setDiscriminator(QString discriminator);
    QString getAvatar();
    void setAvatar(QString avatar);
    QJsonValue getBot();
    void setBot(QJsonValue bot);
    QJsonValue getSystem();
    void setSystem(QJsonValue system);
    QJsonValue getMfaEnabled();
    void setMfaEnabled(QJsonValue mfa_enabled);
    QString getLocale();
    void setLocale(QString locale);
    QJsonValue getVerified();
    void setVerified(QJsonValue verified);
    QString getEmail();
    void setEmail(QString email);
    QJsonValue getFlags();
    void setFlags(QJsonValue flags);
    QJsonValue getPremiumType();
    void setPremiumType(QJsonValue premium_type);
    QJsonValue getPublicFlags();
    void setPublicFlags(QJsonValue public_flags);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(User)

#endif // USER_H
