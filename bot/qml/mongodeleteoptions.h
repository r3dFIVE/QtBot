#ifndef MONGODELETEOPTIONS_H
#define MONGODELETEOPTIONS_H

#include <QObject>
#include <QJsonObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/delete.hpp>

#endif

class MongoDeleteOptions : public QObject
{
    Q_OBJECT

    mongocxx::options::delete_options _deleteOptions{};

    static const QString COLLATION;
    static const QString HINT;

public:
    static mongocxx::options::delete_options fromJson(const QJsonObject &options);
    static mongocxx::options::delete_options fromVariant(const QVariant &options);

    MongoDeleteOptions(QObject *parent = nullptr) : QObject(parent) {}
    MongoDeleteOptions(const MongoDeleteOptions &other, QObject *parent = nullptr);

    Q_INVOKABLE void collation(const QJsonObject &json);
    Q_INVOKABLE QJsonObject collation() const;
    Q_INVOKABLE void hint(const QJsonObject &json);
    Q_INVOKABLE QJsonObject hint() const;

    mongocxx::options::delete_options get();
};

#endif // MONGODELETEOPTIONS_H
