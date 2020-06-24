#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializable.h"
#include "user.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class Emoji : public JsonSerializable
{
    Q_OBJECT

public:
    const QString ID = "id";
    const QString NAME = "name";
    const QString ROLES = "roles";
    const QString USER = "user";
    const QString REQUIRE_COLONS = "require_colons";
    const QString MANAGED = "managed";
    const QString ANIMATED = "animated";
    const QString AVAILABLE = "available";

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;

    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    QList<QString> roles;

    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    QSharedPointer<User> user;

    Q_PROPERTY(QJsonValue require_colons READ getRequireColons WRITE setRequireColons)
    QSharedPointer<bool> require_colons;

    Q_PROPERTY(QJsonValue managed READ getManaged WRITE setManaged)
    QSharedPointer<bool> managed;

    Q_PROPERTY(QJsonValue animated READ getAnimated WRITE setAnimated)
    QSharedPointer<bool> animated;

    Q_PROPERTY(QJsonValue available READ getAvailable WRITE setAvailable)
    QSharedPointer<bool> available;

    QString getId();
    void setId(QString id);
    QString getName();
    void setName(QString name);
    QJsonArray getRoles();
    void setRoles(QJsonArray roles);
    QJsonObject getUser();
    void setUser(QJsonObject user);
    QJsonValue getRequireColons();
    void setRequireColons(QJsonValue require_colons);
    QJsonValue getManaged();
    void setManaged(QJsonValue managed);
    QJsonValue getAnimated();
    void setAnimated(QJsonValue animated);
    QJsonValue getAvailable();
    void setAvailable(QJsonValue available);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

#endif // EMOJI_H
