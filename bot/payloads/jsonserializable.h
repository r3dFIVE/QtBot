#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class JsonSerializable : public QObject
{
    Q_OBJECT

    virtual void read(const QJsonObject &jsonObject) = 0;
    virtual void write(QJsonObject &jsonObject) = 0;

public:
    JsonSerializable() {}
    JsonSerializable(const JsonSerializable &serializeable) { Q_UNUSED(serializeable) }
    ~JsonSerializable() {}


    QJsonObject toQJsonObject();
    QByteArray toByteArray();
    QString toQString();
    void fromQJsonObject(const QJsonObject &json);
    void fromQString(const QString &json);
    void fromByteArray(const QByteArray &json);
};

Q_DECLARE_METATYPE(JsonSerializable*)

#endif // JSONSERIALIZEABLE_H
