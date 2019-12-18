#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include <QJsonObject>
#include <QObject>


class JsonSerializeable : public QObject {
    Q_OBJECT
public:
    JsonSerializeable() {}
    JsonSerializeable(const JsonSerializeable &serializeable) { Q_UNUSED(serializeable) }
    ~JsonSerializeable() {}
    virtual void read(const QJsonObject &jsonObject) = 0;
    virtual void write(QJsonObject &jsonObject) const = 0;
};
Q_DECLARE_METATYPE(JsonSerializeable*)
#endif // JSONSERIALIZEABLE_H
