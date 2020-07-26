#ifndef ENUMUTILS_H
#define ENUMUTILS_H

#include <QObject>
#include <QMetaEnum>


class EnumUtils : public QObject
{
    Q_OBJECT
public:
    template <class T>
    static QString valueToKey(T t) {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();
        return metaEnum.valueToKey(t);
    };

    template <class T>
    static int keyToValue(QByteArray key) {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();
        return metaEnum.keyToValue(key);
    }
};

#endif // ENUMUTILS_H
