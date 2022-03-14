#ifndef MONGODELETEOPTIONS_H
#define MONGODELETEOPTIONS_H

#include <QObject>
#include <QJsonObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/delete.hpp>

#endif

#include "logging/logfactory.h"


class MongoDeleteOptions : public QObject
{
    Q_OBJECT

    mongocxx::options::delete_options _deleteOptions{};

    static const QString COLLATION;
    static const QString HINT;

    static Logger* getLogger() {
        return LogFactory::getLogger("MongoFindOptions");
    }

public:
    static mongocxx::options::delete_options fromJson(const QJsonObject &options);
    static mongocxx::options::delete_options fromVariant(const QVariant &options);

    MongoDeleteOptions(QObject *parent = nullptr) : QObject(parent) {}
    MongoDeleteOptions(const MongoDeleteOptions &other, QObject *parent = nullptr);
    ~MongoDeleteOptions() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        getLogger()->trace(QString("Destroyed MongoDeleteOptions(%1)").arg(ptrStr));
    }

    Q_INVOKABLE void collation(const QJsonObject &json);
    Q_INVOKABLE QJsonObject collation() const;
    Q_INVOKABLE void hint(const QJsonObject &json);
    Q_INVOKABLE QJsonObject hint() const;

    mongocxx::options::delete_options get();
};

#endif // MONGODELETEOPTIONS_H
