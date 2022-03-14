#ifndef MONGODB_H
#define MONGODB_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#ifndef Q_MOC_RUN

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/types/bson_value/view.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/exception/exception.hpp>

#endif

#include "botjob/databasecontext.h"
#include "file.h"
#include "tempfile.h"
#include "logging/logfactory.h"


class MongoDB : public QObject
{
    Q_OBJECT

    static const int TEN_MEGABYTES;
    static const std::string ATTACHMENTS;
    static const std::string ATTACHMENTS_FILES;
    static const std::string ATTACHMENTS_CHUNKS;

    Logger *_logger = LogFactory::getLogger(this);
    DatabaseContext _databaseContext;

    std::string _databaseName;
    std::string _collectionName;

    mongocxx::options::find parseFindOpts(const QVariant &opts);
    mongocxx::options::insert parseInsertOpts(const QVariant &opts);

    Q_INVOKABLE TempFile* findFileByChecksum(const QString &checksum, mongocxx::client &client, const QString &filename = QString());

public:
    MongoDB(QObject *parent = nullptr);
    MongoDB(const MongoDB &other, QObject *parent = nullptr);
    MongoDB(const DatabaseContext &context, QObject *parent = nullptr);
    ~MongoDB() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed MongoDB(%1)").arg(ptrStr));
    }

    Q_INVOKABLE QString collectionName();

    void deleteOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::delete_options &options);
    void deleteMany(const bsoncxx::document::view_or_value &filter, const mongocxx::options::delete_options &options);
    void insertOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::insert &options);
    QJsonArray find(const bsoncxx::document::view_or_value &filter, const mongocxx::options::find &options);
    QJsonObject findOne(const bsoncxx::document::view_or_value &filter, const mongocxx::options::find &options);
    void updateOne(const bsoncxx::document::view_or_value &filter,
                   const bsoncxx::document::view_or_value &update,
                   const mongocxx::options::update &options);
    void updateMany(const bsoncxx::document::view_or_value &filter,
                    const bsoncxx::document::view_or_value &update,
                    const mongocxx::options::update &options);

    Q_INVOKABLE void deleteOne(const QVariant &filter, const QJsonObject &options = QJsonObject());
    Q_INVOKABLE void deleteOne(const QVariant &filter, const QVariant &options);
    Q_INVOKABLE void deleteMany(const QVariant &filter, const QJsonObject &options = QJsonObject());
    Q_INVOKABLE void deleteMany(const QVariant &filter, const QVariant &options);
    Q_INVOKABLE void insertOne(const QVariant &filter, const QJsonObject &options = QJsonObject());
    Q_INVOKABLE void insertOne(const QVariant &filter, const QVariant &options);
    Q_INVOKABLE QJsonArray find(const QVariant &filter, const QJsonObject &options = QJsonObject());
    Q_INVOKABLE QJsonArray find(const QVariant &filter, const QVariant &options);
    Q_INVOKABLE QJsonObject findOne(const QVariant &filter, const QJsonObject &options = QJsonObject());
    Q_INVOKABLE QJsonObject findOne(const QVariant &filter, const QVariant &options);
    Q_INVOKABLE void updateOne(const QVariant &filter, const QVariant &update, const QJsonObject &options = QJsonObject());
    Q_INVOKABLE void updateOne(const QVariant &filter, const QVariant &update, const QVariant &options);
    Q_INVOKABLE void updateMany(const QVariant &filter, const QVariant &update, const QJsonObject &options = QJsonObject());
    Q_INVOKABLE void updateMany(const QVariant &filter, const QVariant &update, const QVariant &options);
    Q_INVOKABLE void databaseName(const QString &databaseName);
    Q_INVOKABLE QString databaseName();
    Q_INVOKABLE void collectionName(const QString &collectionName);
    Q_INVOKABLE QString hostName();
    Q_INVOKABLE void hostName(const QString &hostName);
    Q_INVOKABLE QString password();
    Q_INVOKABLE void password(const QString &password);
    Q_INVOKABLE int port();
    Q_INVOKABLE void port(int port);
    Q_INVOKABLE QString userName();
    Q_INVOKABLE void userName(const QString &userName);
    Q_INVOKABLE TempFile* findFileByChecksum(const QString &checksum, const QString &filename = QString());
    Q_INVOKABLE QVariantList findFilesByMessageId(const QString &messageId);
};

Q_DECLARE_METATYPE(MongoDB)

#endif // MONGODB_H
