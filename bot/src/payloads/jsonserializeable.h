#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include <QJsonObject>
#include <QObject>
#include <QJsonDocument>


class JsonSerializeable : public QObject
{
    Q_OBJECT

    virtual void read(const QJsonObject &jsonObject) = 0;
    virtual void write(QJsonObject &jsonObject) const = 0;

public:
    JsonSerializeable() {}
    JsonSerializeable(const JsonSerializeable &serializeable) { Q_UNUSED(serializeable) }
    ~JsonSerializeable() {}


    QJsonObject toQJsonObject() const {
        QJsonObject jsonObject;
        this->write(jsonObject);
        return jsonObject;
    }

    QByteArray toByteArray() const {
        QJsonDocument document(this->toQJsonObject());
        return document.toJson(QJsonDocument::Compact);
    }

    QString toQString() const {
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
Q_DECLARE_METATYPE(JsonSerializeable*)
#endif // JSONSERIALIZEABLE_H
