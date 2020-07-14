#ifndef ROUTE_H
#define ROUTE_H

#include "payloads/jsonserializable.h"
#include "payloads/message.h"

#include <QNetworkRequest>
#include <QObject>


class Route : public QObject
{
    Q_OBJECT

protected:
    QByteArray _payload;
    QNetworkRequest _request;

    const QString DISCORD_API_PATH = "https://discord.com/api";
    const QString CHANNEL_ID_TOKEN = "{channel.id}";
    const QString GUILD_ID_TOKEN = "{guild.id}";
    const QString WEBHOOK_ID_TOKEN = "{webhook.id}";

    inline void buildRequest(QString url) {
        _request = QNetworkRequest(QUrl(url));
        _request.setRawHeader("User-Agent", "QtBot 0.3");
        _request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    }

public:

    Route() {}
    Route(const Route &other) { Q_UNUSED(other) }
    ~Route() {}

    enum RequestType {
        POST,       // C
        GET,        // R
        PUT,        // U (Update/Replace)
        PATCH,      // U (Update/Modify)
        DELETE,     // D
    };
    Q_ENUM(RequestType);

    enum Bucket {
        CHANNEL_ID,
        GUILD_ID,
        WEBHOOK_ID,
        GLOBAL
    };
    Q_ENUM(Bucket)

    virtual QNetworkRequest request() = 0;
    virtual QByteArray payload() = 0;

    inline void addRawHeader(const QByteArray &headerName, const QByteArray &headerValue) {
        _request.setRawHeader(headerName, headerValue);
    }

    static const QString PATH;
    static const RequestType REQUEST_TYPE;
    static const Bucket BUCKET;
};

Q_DECLARE_METATYPE(Route*)

#endif // ROUTE_H
