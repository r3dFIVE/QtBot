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
    enum RequestType {
        POST,       // C
        GET,        // R
        PUT,        // U (Update/Replace)
        PATCH,      // U (Update/Modify)
        DELETE,     // D
    };
    Q_ENUM(RequestType);

    enum Bucket {
        CHANNEL_ID_BUCKET,
        GUILD_ID_BUCKET,
        WEBHOOK_ID_BUCKET,
        GLOBAL_BUCKET
    };

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

    inline Bucket getBucket() {
        return _bucket;
    }

protected:
    Route() {}
    Route(const Route &other) { Q_UNUSED(other) }
    ~Route() {}

    QByteArray _payload;
    QNetworkRequest _request;
    RequestType _requestType;
    Bucket _bucket;

    Q_ENUM(Bucket)

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

    void buildRequest(const QString &endpoint, const RequestType requestType,
                      const Bucket bucket, const EventContext &context);

    void populateToken(const QString &path, const QString &token, const EventContext &context);
};


#endif // ROUTE_H
