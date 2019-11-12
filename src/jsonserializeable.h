#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include <QJsonObject>


class JsonSerializeable {

public:
    virtual ~JsonSerializeable() {}
    virtual void read(const QJsonObject &jsonObject) = 0;
    virtual void write(QJsonObject &jsonObject) const = 0;
};

#endif // JSONSERIALIZEABLE_H
