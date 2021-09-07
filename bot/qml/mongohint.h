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
    static const QString TYPE_NAME;

    MongoHint() {};
    MongoHint(const QJsonObject &hint);
    MongoHint(const MongoHint &other);

    Q_INVOKABLE MongoHint& operator=(const MongoHint &other);

    Q_INVOKABLE QJsonObject toValue();
};

Q_DECLARE_METATYPE(MongoHint);

#endif // MONGOHINT_H
