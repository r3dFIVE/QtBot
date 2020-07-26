#include "httpclient.h"
#include "util/globals.h"
#include "routes/createmessage.h"

#include <QEventLoop>
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>


const QByteArray HttpClient::X_RATELIMIT_RESET = "x-ratelimit-reset";
const QByteArray HttpClient::X_RATELIMIT_REMAINING = "x-ratelimit-remaining";
const QByteArray HttpClient::X_RATELIMIT_LIMIT = "x-ratelimit-limit";

int HttpClient::_channelRequestRemaining = 1;
int HttpClient::_guildRequestRemaining = 1;
int HttpClient::_webhookRequestRemaining = 1;
int HttpClient::_globalRequestRemaining = 1;

qint64 HttpClient::_channelRequestResetAt = 1;
qint64 HttpClient::_guildRequestResetAt = 1;
qint64 HttpClient::_webhookRequestResetAt = 1;
qint64 HttpClient::_globalRequestResetAt = 1;

QMutex HttpClient::_channelLock;
QMutex HttpClient::_guildLock;
QMutex HttpClient::_webhookLock;
QMutex HttpClient::_globalLock;

QMap<int, QString> HttpClient::_bucketMap;

HttpClient::HttpClient(const QString &botToken) :
    _botAuthHeaderName(QString("Authorization").toUtf8()),
    _botAuthHeaderValue(QString("Bot %1").arg(botToken).toUtf8())
{
    _logger = LogFactory::getLogger();

    buildBucketMap();
}

QSharedPointer<EventContext>
HttpClient::processRoute(Route &route) {
    QNetworkAccessManager networkManager;

    QNetworkReply *reply;

    bool bucketAvailable = true;
    int resetAt = 0;

    switch (route.BUCKET) {
        case Route::CHANNEL_ID: {

            QMutexLocker lock(&_channelLock);

            if (HttpClient::_channelRequestRemaining != 0
                    || QDateTime::currentSecsSinceEpoch() > _channelRequestResetAt) {
                reply = executeRoute(networkManager, route);                
            } else {
                bucketAvailable = false;
                resetAt = _channelRequestResetAt;
            }

            break;
        }
        case Route::GUILD_ID: {

            QMutexLocker lock(&_guildLock);

            if (_guildRequestRemaining != 0
                    || QDateTime::currentSecsSinceEpoch() > _guildRequestResetAt) {
                reply = executeRoute(networkManager, route);
            } else {
                bucketAvailable = false;
                resetAt = HttpClient::_guildRequestResetAt;
            }

            break;            
        } case Route::WEBHOOK_ID: {

            QMutexLocker lock(&_webhookLock);

            if (_webhookRequestRemaining != 0
                    || QDateTime::currentSecsSinceEpoch() > _webhookRequestResetAt) {
                reply = executeRoute(networkManager, route);
            } else {
                bucketAvailable = false;
                resetAt = _webhookRequestResetAt;
            }

            break;            
        } case Route::GLOBAL: {

            QMutexLocker lock(&_globalLock);

            if (_globalRequestRemaining != 0
                    || QDateTime::currentSecsSinceEpoch() > _globalRequestResetAt) {
                reply = executeRoute(networkManager, route);
            } else {
                bucketAvailable = false;
                resetAt = _globalRequestResetAt;
            }

            break;            
        }
    }

    QSharedPointer<EventContext> context;

    if (bucketAvailable) {
        QByteArray response(reply->readAll());

        _logger->trace("Discord API Response: " + response);

        context = QSharedPointer<EventContext>(new EventContext(response));
    } else {
        _logger->warning(QString("Rate limit reached for bucket: %1. Limit resets at: %2")
                            .arg(HttpClient::_bucketMap[route.BUCKET])
                            .arg(QDateTime::fromSecsSinceEpoch(resetAt).toString()));
    }

    return context;
}



QNetworkReply*
HttpClient::executeRoute(QNetworkAccessManager &networkManager, Route &route) {
    QNetworkReply *reply;

    route.addRawHeader(_botAuthHeaderName, _botAuthHeaderValue);

    switch (route.REQUEST_TYPE) {
        case Route::POST: {
            reply = networkManager.post(route.request(), route.payload());
            break;
        } case Route::GET: {
            reply = networkManager.get(route.request());
            break;
        } case Route::PUT: {
            reply = networkManager.put(route.request(), route.payload());
            break;
        } case Route::PATCH: {
            reply = networkManager.sendCustomRequest(route.request(), "PATCH", route.payload());
            break;
        } case Route::DELETE: {
            reply = networkManager.deleteResource(route.request());
            break;
        }
    }

    waitForReply(reply);

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode >= 200 && statusCode < 300) {
        updateRateLimit(route.BUCKET, reply);
    }

    return reply;
}

void
HttpClient::updateRateLimit(Route::Bucket bucket, QNetworkReply *reply) {
    QString rateLimitResetAtString = QString(reply->rawHeader(X_RATELIMIT_RESET));
    QString rateLimitRemainingString = QString(reply->rawHeader(X_RATELIMIT_REMAINING));
    QString rateLimit = QString(reply->rawHeader(X_RATELIMIT_LIMIT));

    int rateLimitResetAt = rateLimitResetAtString.toUInt();

    switch(bucket) {
        case Route::CHANNEL_ID: {
            _channelRequestResetAt = rateLimitResetAt;
            _channelRequestRemaining = rateLimitRemainingString.toUInt();
            break;
        } case Route::GUILD_ID:
            _guildRequestResetAt = rateLimitResetAt;
            _guildRequestRemaining = rateLimitRemainingString.toUInt();
            break;
        case Route::WEBHOOK_ID:
            _webhookRequestResetAt = rateLimitResetAt;
            _webhookRequestRemaining = rateLimitRemainingString.toUInt();
            break;
        case Route::GLOBAL:
            _globalRequestResetAt = rateLimitResetAt;
            _globalRequestRemaining = rateLimitRemainingString.toUInt();
            break;
    }

    _logger->trace(QString("Rate Limited updated for bucket: %1. Rate Limit reimaining: %2/%3. Rate limit resets at: %3")
                   .arg(_bucketMap[bucket])
                   .arg(rateLimitRemainingString)
                   .arg(rateLimit)
                   .arg(QDateTime::fromSecsSinceEpoch(rateLimitResetAt).toString()));
}

void
HttpClient::waitForReply(QNetworkReply *reply) {
    QEventLoop loop;

    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();
}
