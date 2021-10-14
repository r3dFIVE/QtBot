#ifndef MONGOINSERT_H
#define MONGOINSERT_H

#include <QObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/insert.hpp>

#endif


class MongoInsert : public QObject
{
    Q_OBJECT

    mongocxx::options::insert _insertOpts{};

public:
    MongoInsert(QObject *parent = nullptr) : QObject(parent) {}
    MongoInsert(const MongoInsert &other, QObject *parent = nullptr);
    ~MongoInsert() {}

    MongoInsert& operator=(const MongoInsert &other);

    Q_INVOKABLE bool bypassDocumentValidation();
    Q_INVOKABLE void bypassDocumentValidation(const bool bypass);
    Q_INVOKABLE bool ordered();
    Q_INVOKABLE void ordered(const bool ordered);

    mongocxx::options::insert get();
};

Q_DECLARE_METATYPE(MongoInsert)

#endif // MONGOINSERT_H
