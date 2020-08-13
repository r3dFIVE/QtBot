#ifndef ENUMUTILS_H
#define ENUMUTILS_H

#include <QObject>
#include <QMetaEnum>
#include <QJsonValue>


class EnumUtils : public QObject
{
    Q_OBJECT

public:
    template <class T>
    static QString valueToKey(const T &t) {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return metaEnum.valueToKey(t);
    };

    template <class T>
    static int keyToValue(const int &key) {
        QByteArray byteArray;

        byteArray.setNum(key);

        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return metaEnum.keyToValue(byteArray);
    }

    template <class T>
    static T keyToValue(const QByteArray &key) {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return (T) metaEnum.keyToValue(key);
    }

    template <class T>
    static T keyToValue(const QJsonValue &json) {
        QByteArray key = json.toString().toUtf8();

        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return (T) metaEnum.keyToValue(key);
    }
};

#endif // ENUMUTILS_H
