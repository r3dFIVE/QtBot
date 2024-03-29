#ifndef MONGOUTILS_H
#define MONGOUTILS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#ifndef Q_MOC_RUN

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/types/bson_value/view.hpp>
#include <bsoncxx/stdx/optional.hpp>

#endif

#include "botjob/databasecontext.h"
#include "logging/logfactory.h"

class MongoUtils : public QObject
{
    Q_OBJECT

    static Logger* getLogger() {
        return LogFactory::getLogger("MongoUtils");
    }

public:

    QString
    static toQString(const bsoncxx::document::value &value) {
        return QString::fromStdString(bsoncxx::to_json(value));
    }


    QString
    static toQString(const bsoncxx::types::bson_value::view &view) {
       return QString::fromStdString(view.get_utf8().value.to_string());
    }

    QJsonObject
    static toJson(const bsoncxx::document::value &value) {
        QString valueStr = QString::fromStdString(bsoncxx::to_json(value));

        return QJsonDocument::fromJson(valueStr.toUtf8()).object();
    }

    QJsonObject
    static toJson(const bsoncxx::types::bson_value::view &view) {
       QString valueStr = QString::fromStdString(view.get_utf8().value.to_string());

       return  QJsonDocument::fromJson(valueStr.toUtf8()).object();
    }

    QJsonObject
    static toJson(const bsoncxx::document::view_or_value &view_or_value) {    
        QString valueStr = QString::fromStdString(bsoncxx::to_json(view_or_value.view()));

        return QJsonDocument::fromJson(valueStr.toUtf8()).object();
    }

    bsoncxx::document::view_or_value
    static toViewOrValue(const QVariant &variant) {
        try {
            auto doc = QJsonDocument(QJsonObject::fromVariantMap(variant.toMap())).toJson(QJsonDocument::Compact);

            return bsoncxx::from_json(doc.toStdString());
        } catch (const mongocxx::exception &e) {
            getLogger()->warning(QString("Failed to convert to bsoncxx::document::view_or_value from QVariant. REASON: %1").arg(e.what()));

            return bsoncxx::builder::basic::document().extract();
        }
    }

    bsoncxx::document::view_or_value
    static toViewOrValue(const QJsonObject &json) {
        try {
            auto jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

            return bsoncxx::from_json(jsonData.toStdString());
        } catch (const mongocxx::exception &e) {
            getLogger()->warning(QString("Failed to convert to bsoncxx::document::view_or_value from QJsonObject. REASON: %1").arg(e.what()));

            return bsoncxx::builder::basic::document().extract();
        }
    }


    mongocxx::uri
    static buildUri(const DatabaseContext &ctx) {
        QString uri("mongodb://");

        bool requiresAuth = false;

        if (!ctx.userName.isEmpty()) {
            uri.append(QString("%1:%2@").arg(ctx.userName).arg(ctx.password));

            requiresAuth = true;
        }

        QString hostPort = QString("%1:%2").arg(ctx.hostName).arg(ctx.port);

        uri.append(hostPort);

        uri.append(QString("/?maxPoolSize=%1").arg(ctx.maxPoolSize));

        if (requiresAuth) {
            uri.append("&authSource=admin");
        }

        return mongocxx::uri{uri.toStdString()};
    }

};

#endif // MONGOUTILS_H
