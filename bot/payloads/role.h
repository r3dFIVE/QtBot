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

    QString getId();
    void setId(QString id);
    QString getName();
    void setName(QString name);
    int getColor();
    void setColor(int color);
    bool getHoist();
    void setHoist(bool hoist);
    int getPosition();
    void setPosition(int position);
    int getPermissions();
    void setPermissions(int permissions);
    bool getManaged();
    void setManaged(bool managed);
    bool getMentionable();
    void setMentionable(bool mentionable);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(Role)

#endif // ROLE_H
