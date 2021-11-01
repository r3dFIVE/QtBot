#ifndef MONGOUPDATEOPTIONS_H
#define MONGOUPDATEOPTIONS_H

#include <QJsonObject>
#include <QJsonValue>
#include <QObject>

#ifndef Q_MOC_RUN

#include <mongocxx/options/update.hpp>

#endif



class MongoUpdateOptions : public QObject
{
    Q_OBJECT

    mongocxx::options::update _updateOptions;

    static const QString BYPASS_DOCUMENT_VALIDATION;
    static const QString COLLATION;
    static const QString UPSERT;
    static const QString HINT;

public:
    MongoUpdateOptions(QObject *parent = nullptr) : QObject(parent) {}
    MongoUpdateOptions(const MongoUpdateOptions &other, QObject *parent = nullptr);
    ~MongoUpdateOptions() {}

    Q_INVOKABLE MongoUpdateOptions& operator=(const MongoUpdateOptions &other);

    static mongocxx::options::update fromJson(const QJsonObject &options);
    static mongocxx::options::update fromVariant(const QVariant &options);

    Q_INVOKABLE void bypassDocumentValidation(const bool bypass);
    Q_INVOKABLE bool bypassDocumentValidation();
    Q_INVOKABLE void collation(const QJsonObject &json);
    Q_INVOKABLE QJsonObject collation();
    Q_INVOKABLE void upsert(const bool upsert);
    Q_INVOKABLE bool upsert();
    Q_INVOKABLE void hint(const QJsonObject &json);
    Q_INVOKABLE QJsonObject hint();

    mongocxx::options::update get();
};

Q_DECLARE_METATYPE(MongoUpdateOptions)

#endif // MONGOUPDATEOPTIONS_H
