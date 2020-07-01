#ifndef MESSAGEAPPLICATION_H
#define MESSAGEAPPLICATION_H

#include "jsonserializable.h"

#include <QObject>

class MessageApplication : public JsonSerializable
{
    Q_OBJECT

public:
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    QJsonValue type;

    Q_PROPERTY(QJsonValue cover_image READ getCoverImage WRITE setCoverImage)
    QJsonValue cover_image;

    Q_PROPERTY(QJsonValue description READ getDescription WRITE setDescription)
    QJsonValue description;

    Q_PROPERTY(QJsonValue icon READ getIcon WRITE setIcon)
    QJsonValue icon;

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    QJsonValue name;

    QJsonValue getType() const;
    void setType(const QJsonValue &value);
    QJsonValue getCoverImage() const;
    void setCoverImage(const QJsonValue &value);
    QJsonValue getDescription() const;
    void setDescription(const QJsonValue &value);
    QJsonValue getIcon() const;
    void setIcon(const QJsonValue &value);
    QJsonValue getName() const;
    void setName(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    MessageApplication() {}
    ~MessageApplication() {}
};

Q_DECLARE_METATYPE(MessageApplication)
#endif // MESSAGEAPPLICATION_H
