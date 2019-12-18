#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "jsonserializeable.h"


class JsonSerializer {
public:
    static QString toQString(const JsonSerializeable &serializeable);
    static QByteArray toByteArray(const JsonSerializeable &serializeable);
    static QJsonObject toQJsonObject(const JsonSerializeable &serializeable);
    static void fromByteArray(JsonSerializeable &serializeable, const QByteArray &json);
    static void fromQString(JsonSerializeable &serializeable, const QString &json);
    static void fromQJsonObject(JsonSerializeable &serializeable, const QJsonObject &json);
};

#endif // JSONSERIALIZER_H
