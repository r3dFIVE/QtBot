#ifndef EMBEDFIELD_H
#define EMBEDFIELD_H

#include "jsonserializable.h"

#include <QObject>

class EmbedField : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    QJsonValue name;

    Q_PROPERTY(QJsonValue value READ getValue WRITE setValue)
    QJsonValue value;

    Q_PROPERTY(QJsonValue inline READ getInline WRITE setInline)
    QJsonValue inln;

    QJsonValue getName() const;
    void setName(const QJsonValue &value);
    QJsonValue getValue() const;
    void setValue(const QJsonValue &value);
    QJsonValue getInline() const;
    void setInline(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    EmbedField() {}
    ~EmbedField() {}
};

Q_DECLARE_METATYPE(EmbedField)

#endif // EMBEDFIELD_H
