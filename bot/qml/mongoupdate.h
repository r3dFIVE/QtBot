#ifndef MONGOUPDATE_H
#define MONGOUPDATE_H

#include <QJsonValue>
#include <QObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/update.hpp>

#endif


class MongoUpdate : public QObject
{
    Q_OBJECT

    mongocxx::options::update _updateOpts;

public:
    MongoUpdate(QObject *parent = nullptr) : QObject(parent) {}
    MongoUpdate(const MongoUpdate &other, QObject *parent = nullptr);
    ~MongoUpdate() {}

    Q_INVOKABLE MongoUpdate& operator=(const MongoUpdate &other);

//    Q_INVOKABLE void bypassDocumentValidation(const bool bypass);
//    Q_INVOKABLE bool bypassDocumentValidation();
//    Q_INVOKABLE void collation(const QJsonObject &json);
//    Q_INVOKABLE QJsonObject collation();
//    Q_INVOKABLE void upsert(const bool upsert);
//    Q_INVOKABLE bool upsert();
//    Q_INVOKABLE void hint(const QJsonObject &json);
//    Q_INVOKABLE QJsonObject hint();

    mongocxx::options::update get();
};

Q_DECLARE_METATYPE(MongoUpdate)

#endif // MONGOUPDATE_H
