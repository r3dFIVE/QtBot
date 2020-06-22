#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializable.h"
#include "user.h"


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

    QString
    getId() {
        return id;
    }

    void
    setId(QString id) {
        this->id = id;
    }

    QString
    getName() {
        return name;
    }

    void
    setName(QString name) {
        this->name = name;
    }

    QJsonArray
    getRoles() {
        if (roles.isEmpty()) {
            return QJsonArray();
        } else {
            QJsonArray roleIds;
            for (QString roleId : roles) {
                roleIds.push_back(roleId);
            }
            return roleIds;
        }
    }

    void
    setRoles(QJsonArray roleIds) {
        for (QJsonValue roleId : roleIds) {
            roles.push_back(roleId.toString());
        }
    }

    QJsonObject
    getUser() {
        if (user) {
            return (user->toQJsonObject());
        } else {
            return QJsonObject();
        }
    }

    void
    setUser(QJsonObject user) {
        if (!user.isEmpty()) {
            if (!this->user) {
                this->user = QSharedPointer<User>(new User);
            }
            JsonUtils::readFromJson(*this->user, user);
        }
    }

    QJsonValue
    getRequireColons() {
        if (require_colons) {
            return QJsonValue(*require_colons);
        } else {
            return QJsonValue();
        }
    }

    void
    setRequireColons(QJsonValue require_colons) {
        if (!require_colons.isNull()) {
            this->require_colons = QSharedPointer<bool>(new bool(require_colons.toBool()));
        }
    }

    QJsonValue
    getManaged() {
        if (managed) {
            return QJsonValue(*managed);
        } else {
            return QJsonValue();
        }
    }

    void
    setManaged(QJsonValue managed) {
        if (!managed.isNull()) {
            this->managed = QSharedPointer<bool>(new bool(managed.toBool()));
        }
    }

    QJsonValue
    getAnimated() {
        if (animated) {
            return QJsonValue(*animated);
        } else {
            return QJsonValue();
        }
    }

    void
    setAnimated(QJsonValue animated) {
        if (!animated.isNull()) {
            this->animated = QSharedPointer<bool>(new bool(animated.toBool()));
        }
    }

    QJsonValue
    getAvailable() {
        if (require_colons) {
            return QJsonValue(*require_colons);
        } else {
            return QJsonValue();
        }
    }

    void
    setAvailable(QJsonValue available) {
        if (!available.isNull()) {
            this->available = QSharedPointer<bool>(new bool(available.toBool()));
        }
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

#endif // EMOJI_H
