#ifndef MONGOHINT_H
#define MONGOHINT_H

#include <QObject>
#include <QJsonObject>
#include <QSharedPointer>

#ifndef Q_MOC_RUN

#include <mongocxx/hint.hpp>

#endif


class MongoHint : public QObject
{
    Q_OBJECT

    QSharedPointer<mongocxx::hint> _hint;

public:
    MongoHint(QObject *parent = nullptr) : QObject(parent) {}
    MongoHint(const QJsonObject &hint, QObject *parent = nullptr);
    MongoHint(const MongoHint &other, QObject *parent = nullptr);

    Q_INVOKABLE MongoHint& operator=(const MongoHint &other);

    Q_INVOKABLE QJsonObject toValue();
};

Q_DECLARE_METATYPE(MongoHint);

#endif // MONGOHINT_H
