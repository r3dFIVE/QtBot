#ifndef MONGODB_H
#define MONGODB_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#ifndef Q_MOC_RUN

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>

#endif

#include "botjob/databasecontext.h"
#include "logging/logfactory.h"


class MongoDB : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    int _port;
    std::string _databaseName;
    std::string _collectionName;
    QString _hostName;
    QString _password;
    QString _userName;

    mongocxx::options::find parseFindOpts(const QVariant &opts);
    mongocxx::options::insert parseInsertOpts(const QVariant &opts);

public:
    MongoDB(QObject *parent = nullptr) : QObject(parent) {}
    MongoDB(const MongoDB &other, QObject *parent = nullptr);
    MongoDB(const DatabaseContext &context, QObject *parent = nullptr);
    ~MongoDB() {}

    Q_INVOKABLE QString collectionName();


    Q_INVOKABLE void insertOne(const QVariant &filter, const QVariant &args = QVariant());
    Q_INVOKABLE QJsonArray find(const QVariant &filter, const QVariant &args = QVariant());
    Q_INVOKABLE QJsonObject findOne(const QVariant &filter, const QVariant &args = QVariant());
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
};

Q_DECLARE_METATYPE(MongoDB)

#endif // MONGODB_H
