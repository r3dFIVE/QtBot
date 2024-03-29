#ifndef MONGOINSERTOPTIONS_H
#define MONGOINSERTOPTIONS_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/insert.hpp>

#endif

#include "logging/logfactory.h"

class MongoInsertOptions : public QObject
{
    Q_OBJECT

    static const QString BYPASS_DOCUMENT_VALIDATION;
    static const QString ORDERED;

    static Logger* getLogger() {
        return LogFactory::getLogger("MongoInsertOptions");
    }

    mongocxx::options::insert _insertOptions{};

public:
    MongoInsertOptions(QObject *parent = nullptr) : QObject(parent) {}
    MongoInsertOptions(const MongoInsertOptions &other, QObject *parent = nullptr);
    ~MongoInsertOptions() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        getLogger()->trace(QString("Destroyed MongoInsertOptions(%1)").arg(ptrStr));
    }

    MongoInsertOptions& operator=(const MongoInsertOptions &other);

    static mongocxx::options::insert fromJson(const QJsonObject &options);
    static mongocxx::options::insert fromVariant(const QVariant &options);

    Q_INVOKABLE bool bypassDocumentValidation();
    Q_INVOKABLE void bypassDocumentValidation(const bool bypass);
    Q_INVOKABLE bool ordered();
    Q_INVOKABLE void ordered(const bool ordered);

    mongocxx::options::insert get();
};

Q_DECLARE_METATYPE(MongoInsertOptions)

#endif // MONGOINSERTOPTIONS_H
