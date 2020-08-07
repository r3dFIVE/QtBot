#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializable.h"


class Emoji : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString NAME;
    static const QString ROLES;
    static const QString USER;
    static const QString REQUIRE_COLONS;
    static const QString MANAGED;
    static const QString ANIMATED;
    static const QString AVAILABLE;

    Emoji() {}
    Emoji(const QByteArray &json) : JsonSerializable(json) {}
    Emoji(const QJsonObject &json) : JsonSerializable(json) {}
    Emoji(const QString &json) : JsonSerializable(json) {}

    QJsonArray getRoles() const;
    QJsonObject getUser() const;
    QJsonValue getAnimated() const;
    QJsonValue getAvailable() const;
    QJsonValue getId() const;
    QJsonValue getManaged() const;
    QJsonValue getName() const;
    QJsonValue getRequireColons() const;
    void setAnimated(const QJsonValue &animated);
    void setAvailable(const QJsonValue &available);
    void setId(const QJsonValue &id);
    void setManaged(const QJsonValue &managed);
    void setName(const QJsonValue &name);
    void setRequireColons(const QJsonValue &requireColons);
    void setRoles(const QJsonArray &roles);
    void setUser(const QJsonObject &user);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    Q_PROPERTY(QJsonValue require_colons READ getRequireColons WRITE setRequireColons)
    Q_PROPERTY(QJsonValue managed READ getManaged WRITE setManaged)
    Q_PROPERTY(QJsonValue animated READ getAnimated WRITE setAnimated)
    Q_PROPERTY(QJsonValue available READ getAvailable WRITE setAvailable)
};

#endif // EMOJI_H
