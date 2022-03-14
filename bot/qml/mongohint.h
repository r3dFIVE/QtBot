#ifndef MONGOHINT_H
#define MONGOHINT_H

#include <QObject>
#include <QJsonObject>
#include <QSharedPointer>

#ifndef Q_MOC_RUN

#include <mongocxx/hint.hpp>

#endif

#include "logging/logfactory.h"

class MongoHint : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);
    QSharedPointer<mongocxx::hint> _hint;

public:
    MongoHint(QObject *parent = nullptr) : QObject(parent) {}
    MongoHint(const QJsonObject &hint, QObject *parent = nullptr);
    MongoHint(const MongoHint &other, QObject *parent = nullptr);
    ~MongoHint() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed MongoHint(%1)").arg(ptrStr));
    }

    Q_INVOKABLE MongoHint& operator=(const MongoHint &other);

    Q_INVOKABLE QJsonObject toValue();
};

Q_DECLARE_METATYPE(MongoHint);

#endif // MONGOHINT_H
