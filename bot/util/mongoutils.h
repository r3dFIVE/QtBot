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

class MongoUtils {   
public:
    bsoncxx::document::view_or_value
    static toViewOrValue(const QJsonObject &json) {
        QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

        return bsoncxx::from_json(jsonData.toStdString());
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
        QJsonObject json;

        try {

            if (view_or_value.view().empty()) {
                LogFactory::getLogger()->warning(QString("Failed to convert to bsoncxx::document::value from variant. Reason: View was empty"));

            } else {
                QString valueStr = QString::fromStdString(bsoncxx::to_json(view_or_value.view()));

                json = QJsonDocument::fromJson(valueStr.toUtf8()).object();
            }

        } catch (const mongocxx::exception &e) {
            LogFactory::getLogger()->warning(QString("Failed to convert to bsoncxx::document::value from variant. Reason: %1").arg(e.what()));
        }

        return json;
    }

    bsoncxx::document::view_or_value
    static fromVariant(const QVariant &variant) {
        try {
            auto doc = QJsonDocument(QJsonObject::fromVariantMap(variant.toMap())).toJson(QJsonDocument::Compact);

            return bsoncxx::from_json(doc.toStdString());
        } catch (const mongocxx::exception &e) {
            LogFactory::getLogger()->warning(QString("Failed to convert to bsoncxx::document::value from variant. Reason: %1").arg(e.what()));

            return bsoncxx::builder::basic::document().extract();
        }
    }



    mongocxx::uri
    static buildUri(const DatabaseContext &ctx) {
        QString uri("mongodb://");

        bool requiresAuth = false;

        if (!ctx.userName.isEmpty()) {
            uri.append(QString("%1:%2@").arg(ctx.userName.arg(ctx.password)));

            requiresAuth = true;
        }

        QString hostPort = QString("%1:%2").arg(ctx.hostName).arg(ctx.port);

        uri.append(hostPort);

        uri.append(QString("/?minPoolSize=%1&maxPoolSize=%2").arg(ctx.minPoolSize).arg(ctx.maxPoolSize));

        if (requiresAuth) {
            uri.append("&authSource=admin");
        }

        return mongocxx::uri{uri.toStdString()};
    }

};

#endif // MONGOUTILS_H
