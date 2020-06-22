#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include "jsonutils.h"

#include <QJsonObject>
#include <QObject>
#include <QJsonDocument>

class JsonSerializable : public QObject
{
    Q_OBJECT

    virtual void read(const QJsonObject &jsonObject) = 0;
    virtual void write(QJsonObject &jsonObject) = 0;

public:
    JsonSerializable() {}
    JsonSerializable(const JsonSerializable &serializeable) { Q_UNUSED(serializeable) }
    ~JsonSerializable() {}


    QJsonObject toQJsonObject() {
        QJsonObject jsonObject;
        this->write(jsonObject);
        return jsonObject;
    }

    QByteArray toByteArray() {
        QJsonDocument document(this->toQJsonObject());
        return document.toJson(QJsonDocument::Compact);
    }

    QString toQString() {
        return QString(this->toByteArray());
    }

    void fromQJsonObject(const QJsonObject &json) {
        this->read(json);
    }

    void fromQString(const QString &json) {
        this->fromByteArray(json.toUtf8());
    }

    void fromByteArray(const QByteArray &json) {
        QJsonDocument document = QJsonDocument::fromJson(json);
        QJsonObject object = document.object();
        this->read(object);
    }

};

Q_DECLARE_METATYPE(JsonSerializable*)
#endif // JSONSERIALIZEABLE_H
