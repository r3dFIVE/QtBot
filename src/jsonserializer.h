#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "jsonserializeable.h"


class JsonSerializer {
public:
    static QString toQString(JsonSerializeable &serializeable);
    static QByteArray toByteArray(JsonSerializeable &serializeable);
    static void fromByteArray(const QByteArray &json, JsonSerializeable &serializeable);
    static void fromQString(const QString &json, JsonSerializeable &serializeable);
};

#endif // JSONSERIALIZER_H
