#ifndef MONGOFINDOPTIONS_H
#define MONGOFINDOPTIONS_H

#include <QJsonObject>
#include <QObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/find.hpp>

#endif

#include "logging/logfactory.h"


class MongoFindOptions : public QObject
{
    Q_OBJECT

    static const QString ALLOW_DISK_USE;
    static const QString ALLOW_PARTIAL_RESULTS;
    static const QString BATCH_SIZE;
    static const QString COLLATION;
    static const QString COMMENT;
    static const QString HINT;
    static const QString LIMIT;
    static const QString MAX;
    static const QString MAX_AWAIT_TIME;
    static const QString MAX_TIME;
    static const QString MIN;
    static const QString NO_CURSOR_TIMEOUT;
    static const QString PROJECTION;
    static const QString RETURN_KEY;
    static const QString SHOW_RECORD_ID;
    static const QString SKIP;
    static const QString SORT;

    static Logger* getLogger() {
        return LogFactory::getLogger("MongoFindOptions");
    }

    mongocxx::options::find _findOptions{};

public:
    static mongocxx::options::find fromJson(const QJsonObject &options);
    static mongocxx::options::find fromVariant(const QVariant &options);

    MongoFindOptions(QObject *parent = nullptr) : QObject(parent) {}
    MongoFindOptions(const MongoFindOptions &other, QObject *parent = nullptr);
    ~MongoFindOptions() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        getLogger()->trace(QString("Destroyed MongoFindOptions(%1)").arg(ptrStr));
    }

    MongoFindOptions& operator=(const MongoFindOptions &other);

    Q_INVOKABLE void allowDiskUse(bool allow);
    Q_INVOKABLE bool allowDiskUse() const;
    Q_INVOKABLE void allowPartialResults(bool allow);
    Q_INVOKABLE bool allowPartialResults() const;
    Q_INVOKABLE void batchSize(int batchSize);
    Q_INVOKABLE int batchSize() const;
    Q_INVOKABLE void collation(const QJsonObject &json);
    Q_INVOKABLE QJsonObject collation();
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

Q_DECLARE_METATYPE(MongoFindOptions)

#endif // MONGOFINDOPTIONS_H
