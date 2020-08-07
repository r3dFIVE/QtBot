#ifndef EMBEDFIELD_H
#define EMBEDFIELD_H

#include "jsonserializable.h"


class EmbedField : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString INLINE;
    static const QString NAME;
    static const QString VALUE;

    EmbedField() {}
    EmbedField(const QByteArray &json) : JsonSerializable(json) {}
    EmbedField(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedField(const QString &json) : JsonSerializable(json) {}

    QJsonValue getInline() const;
    QJsonValue getName() const;
    QJsonValue getValue() const;
    void setName(const QJsonValue &name);
    void setValue(const QJsonValue &value);
    void setInline(const QJsonValue &inln);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue value READ getValue WRITE setValue)
    Q_PROPERTY(QJsonValue inline READ getInline WRITE setInline)
};

Q_DECLARE_METATYPE(EmbedField)

#endif // EMBEDFIELD_H
