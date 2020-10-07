#ifndef ROUTE_H
#define ROUTE_H

#include <QNetworkRequest>
#include <QObject>

#include "payloads/eventcontext.h"
#include "payloads/jsonserializable.h"
#include "payloads/message.h"
#include "util/serializationutils.h"


class Route : public QObject
{
    Q_OBJECT

public:
    static const QString GLOBAL_BUCKET;

    enum RequestType {
        POST,       // C
        GET,        // R
        PUT,        // U (Update/Replace)
        PATCH,      // U (Update/Modify)
        DELETE,     // D
    };
    Q_ENUM(RequestType);

    inline QNetworkRequest request() {
        return _request;
    }

    inline QByteArray payload() {
        return _payload;
    }

    inline void addRawHeader(const QByteArray &headerName, const QByteArray &headerValue) {
        _request.setRawHeader(headerName, headerValue);
    }

    inline RequestType getType() {
        return _requestType;
    }


    inline QString getMajorParamId() {
        return _majorParamId;
    }

    inline QString getRouteWithMethod() {
        return _routeWithMethod;
    }

protected:
    Route() {}
    Route(const Route &other) { Q_UNUSED(other) }
    ~Route() {}

    QMap<QString, QString> _pathParams;
    QByteArray _payload;
    QNetworkRequest _request;
    QString _majorParamId;
    QString _routeWithMethod;
    RequestType _requestType;

    const QString DISCORD_API_PATH = "https://discord.com/api";
    const QString CHANNEL_ID_TOKEN = "{channel.id}";
    const QString GUILD_ID_TOKEN = "{guild.id}";
    const QString INTEGRATION_ID_TOKEN = "{integration.id}";
    const QString WEBHOOK_ID_TOKEN = "{webhook.id}";
    const QString MESSAGE_ID_TOKEN = "{message.id}";
    const QString EMOJI_TOKEN = "{emoji}";
    const QString USER_ID_TOKEN = "{user.id}";
    const QString ROLE_ID_TOKEN = "{role.id}";
    const QString OVERWRITE_ID_TOKEN = "{overwrite.id}";

    void buildRequest(const RequestType requestType,
                        const QString &route,
                        const QString &majorParamId,
                        const QJsonObject &payload,
                        const QJsonObject &queryParams = QJsonObject());
};


#endif // ROUTE_H
