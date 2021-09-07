#ifndef MONGOFIND_H
#define MONGOFIND_H

#include <QJsonObject>
#include <QObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/find.hpp>

#endif

#include "logging/logfactory.h"


class MongoFind : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    mongocxx::options::find _findArgs{};

public:
    static const QString TYPE_NAME;

    MongoFind() {}
    MongoFind(const MongoFind &other);
    ~MongoFind() {}

    MongoFind& operator=(const MongoFind &other);

    Q_INVOKABLE void allowDiskUse(bool allow);
    Q_INVOKABLE bool allowDiskUse() const;
    Q_INVOKABLE void allowPartialResults(bool allow);
    Q_INVOKABLE bool allowPartialResults() const;
    Q_INVOKABLE void batchSize(int batchSize);
    Q_INVOKABLE int batchSize() const;
    Q_INVOKABLE void hint(const QJsonObject &json);
    Q_INVOKABLE QJsonObject hint() const;
    Q_INVOKABLE void limit(long hint);
    Q_INVOKABLE long limit() const;
    Q_INVOKABLE void max(const QJsonObject &json);
    Q_INVOKABLE QJsonObject max() const;
    Q_INVOKABLE void maxAwaitTime(long hint);
    Q_INVOKABLE long maxAwaitTime() const;
    Q_INVOKABLE void min(const QJsonObject &json);
    Q_INVOKABLE QJsonObject min() const;
    Q_INVOKABLE void noCursorTimeout(bool timeout);
    Q_INVOKABLE bool noCursorTimeout() const;
    Q_INVOKABLE void projection(const QJsonObject &json);
    Q_INVOKABLE QJsonObject projection() const;
    Q_INVOKABLE void returnKey(bool returnKey);
    Q_INVOKABLE bool returnKey() const;
    Q_INVOKABLE void showRecordId(bool showRecordId);
    Q_INVOKABLE bool showRecordId() const;
    Q_INVOKABLE void skip(long hint);
    Q_INVOKABLE long skip() const;
    Q_INVOKABLE void sort(const QJsonObject &json);
    Q_INVOKABLE QJsonObject sort() const;


    mongocxx::options::find get() const;

};

Q_DECLARE_METATYPE(MongoFind)

#endif // MONGOFIND_H
