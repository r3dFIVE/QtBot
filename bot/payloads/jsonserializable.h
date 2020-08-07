#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class JsonSerializable : public QObject
{
    Q_OBJECT

protected:
    QJsonObject _jsonObject;

public:
    JsonSerializable() {}
    JsonSerializable(const JsonSerializable &other) {
        _jsonObject = other._jsonObject;
    }
    JsonSerializable(const QByteArray &json);
    JsonSerializable(const QJsonObject &json);
    JsonSerializable(const QString &json);
    ~JsonSerializable() {}

    QByteArray toByteArray();
    QJsonObject fromQString(const QString &json);
    QJsonObject fromByteArray(const QByteArray &json);
    QJsonObject toQJsonObject();
    QString toQString();    
    void setQJsonObject(const QJsonObject &jsonObject);
};

Q_DECLARE_METATYPE(JsonSerializable*)

#endif // JSONSERIALIZEABLE_H
