#ifndef ROLE_H
#define ROLE_H

#include "jsonserializable.h"

#include <QObject>

class Role : public JsonSerializable
{
    Q_OBJECT

public:
    const QString ID = "id";
    const QString NAME = "name";
    const QString COLOR = "color";
    const QString HOIST = "hoist";
    const QString POSITION = "position";
    const QString PERMISSIONS = "permissions";
    const QString MANAGED = "managed";
    const QString MENTIONABLE = "mentionable";

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;

    Q_PROPERTY(int color READ getColor WRITE setColor)
    int color;

    Q_PROPERTY(bool hoist READ getHoist WRITE setHoist)
    bool hoist;

    Q_PROPERTY(int position READ getPosition WRITE setPosition)
    int position;

    Q_PROPERTY(int permissions READ getPermissions WRITE setPermissions)
    int permissions;

    Q_PROPERTY(bool managed READ getManaged WRITE setManaged)
    bool managed;

    Q_PROPERTY(bool mentionable READ getMentionable WRITE setMentionable)
    bool mentionable;

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

    int
    getColor() {
        return color;
    }

    void
    setColor(int color) {
        this->color = color;
    }

    bool
    getHoist() {
        return hoist;
    }

    void
    setHoist(bool hoist) {
        this->hoist = hoist;
    }

    int
    getPosition() {
        return position;
    }

    void
    setPosition(int position) {
        this->position = position;
    }

    int
    getPermissions() {
        return permissions;
    }

    void
    setPermissions(int permissions) {
        this->permissions = permissions;
    }

    bool
    getManaged() {
        return managed;
    }

    void
    setManaged(bool managed) {
        this->managed = managed;
    }

    bool
    getMentionable() {
        return mentionable;
    }

    void
    setMentionable(bool mentionable) {
        this->mentionable = mentionable;
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }

};

Q_DECLARE_METATYPE(Role)

#endif // ROLE_H
