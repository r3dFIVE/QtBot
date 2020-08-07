#ifndef ROLE_H
#define ROLE_H

#include "jsonserializable.h"


class Role : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString NAME;
    static const QString COLOR;
    static const QString HOIST;
    static const QString POSITION;
    static const QString PERMISSIONS;
    static const QString MANAGED;
    static const QString MENTIONABLE;

    Role() {}
    Role(const QByteArray &json) : JsonSerializable(json) {}
    Role(const QJsonObject &json) : JsonSerializable(json) {}
    Role(const QString &json) : JsonSerializable(json) {}

    QJsonValue getColor() const;
    QJsonValue getHoist() const;
    QJsonValue getId() const;
    QJsonValue getManaged() const;
    QJsonValue getMentionable() const;
    QJsonValue getName() const;
    QJsonValue getPermissions() const;
    QJsonValue getPosition() const;
    void setColor(const QJsonValue &color);
    void setHoist(const QJsonValue &hoist);
    void setId(const QJsonValue &id);
    void setManaged(const QJsonValue &managed);
    void setMentionable(const QJsonValue &mentionable);
    void setName(const QJsonValue &name);
    void setPermissions(const QJsonValue &permissions);
    void setPosition(const QJsonValue &position);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue color READ getColor WRITE setColor)
    Q_PROPERTY(QJsonValue hoist READ getHoist WRITE setHoist)
    Q_PROPERTY(QJsonValue position READ getPosition WRITE setPosition)
    Q_PROPERTY(QJsonValue permissions READ getPermissions WRITE setPermissions)
    Q_PROPERTY(QJsonValue managed READ getManaged WRITE setManaged)
    Q_PROPERTY(QJsonValue mentionable READ getMentionable WRITE setMentionable)
};

Q_DECLARE_METATYPE(Role)

#endif // ROLE_H
