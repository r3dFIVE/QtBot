#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include <QJsonObject>
#include <QObject>


class JsonSerializeable : public QObject {
    Q_OBJECT
public:
    virtual ~JsonSerializeable() {}
    virtual void read(const QJsonObject &jsonObject) = 0;
    virtual void write(QJsonObject &jsonObject) const = 0;
};
Q_DECLARE_METATYPE(JsonSerializeable*)
#endif // JSONSERIALIZEABLE_H
