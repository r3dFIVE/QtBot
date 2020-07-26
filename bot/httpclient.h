#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QObject>
#include <QMutex>


#include "logging/logfactory.h"
#include "routes/route.h"
#include "qml/eventcontext.h"
#include "util/settings.h"

class HttpClient : public QObject
{
    Q_OBJECT

    Logger *_logger;

    static QMap<int, QString> _bucketMap;

    static QMutex _channelLock;
    static QMutex _guildLock;
    static QMutex _webhookLock;
    static QMutex _globalLock;

    static int _channelRequestRemaining;
    static int _guildRequestRemaining;
    static int _webhookRequestRemaining;
    static int _globalRequestRemaining;

    static qint64 _channelRequestResetAt;
    static qint64 _guildRequestResetAt;
    static qint64 _webhookRequestResetAt;
    static qint64 _globalRequestResetAt;

    static const QByteArray X_RATELIMIT_RESET;
    static const QByteArray X_RATELIMIT_REMAINING;
    static const QByteArray X_RATELIMIT_LIMIT;

    const QByteArray _botAuthHeaderName;
    const QByteArray _botAuthHeaderValue;

    QNetworkReply* processChannelIdBucket(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* processGuildIdBucket(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* processWebhookIdBucket(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* processGlobalBucket(QNetworkAccessManager &networkManager, Route &route);

    QNetworkReply* executeRoute(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* executePost(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* executeGet(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* executePut(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* executePatch(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* executeDelete(QNetworkAccessManager &networkManager, Route &route);

    void addAuthHeader(Route &route);
    void updateRateLimit(const Route::Bucket bucket, QNetworkReply *reply);
    void waitForReply(QNetworkReply *reply);

    inline void buildBucketMap() {
        HttpClient::_bucketMap.insert(0, "CHANNEL_ID");
        HttpClient::_bucketMap.insert(1, "GUILD_ID");
        HttpClient::_bucketMap.insert(2, "WEBHOOK_ID");
        HttpClient::_bucketMap.insert(3, "GLOBAL");
    };

public:
    HttpClient(const QString &botToken);
    QSharedPointer<EventContext> processRoute(Route &route);

};

#endif // HTTPCLIENT_H
