/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "httpclient.h"

#include <QEventLoop>
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>
#include <QtMath>

#include "payloads/ratelimit.h"

const QByteArray HttpClient::X_RATELIMIT_GLOBAL = "x-ratelimit-global";
const QByteArray HttpClient::X_RATELIMIT_RESET = "x-ratelimit-reset";
const QByteArray HttpClient::X_RATELIMIT_REMAINING = "x-ratelimit-remaining";
const QByteArray HttpClient::X_RATELIMIT_LIMIT = "x-ratelimit-limit";
const QByteArray HttpClient::X_RATELIMIT_BUCKET = "x-ratelimit-bucket";

qint64 HttpClient::_globalRequestResetAt = 1;

QMap<QString, QString> HttpClient::_bucketIdByRoute;
QMap<QString, QMap<QString, QSharedPointer<Bucket> > > HttpClient::_bucketMaps;
QReadWriteLock HttpClient::_discoveryLock;


HttpClient::HttpClient(const QString &botToken) :
    _botAuthHeaderName(QString("Authorization").toUtf8()),
    _botAuthHeaderValue(QString("Bot %1").arg(botToken).toUtf8())
{
    _logger = LogFactory::getLogger();
}

QSharedPointer<EventContext>
HttpClient::processRoute(Route &route) {
    QNetworkAccessManager networkManager;

    QString routeWithMethod = route.getRouteWithMethod();

    QSharedPointer<EventContext> context;

    if (_bucketIdByRoute.contains(routeWithMethod)) {
        QString bucketId = _bucketIdByRoute[routeWithMethod];

        if (_bucketMaps[bucketId].contains(route.getMajorParamId())) {
            context = checkBucketAndExecute(networkManager, route);

        } else {
            context = createBucketAndExecute(networkManager, route);
        }
    } else {
        QReadLocker locker(&_discoveryLock);

        // Check that bucket wasnt added during a lock.
        if (_bucketIdByRoute.contains(routeWithMethod)) {
            context = checkBucketAndExecute(networkManager, route);

        } else {
            context = createBucketAndExecute(networkManager, route);
        }
    }

    return context;
}

QSharedPointer<EventContext>
HttpClient::checkBucketAndExecute(QNetworkAccessManager &networkManager, Route &route) {
    QString bucketId = _bucketIdByRoute[route.getRouteWithMethod()];

    QSharedPointer<Bucket> bucket = _bucketMaps[bucketId][route.getMajorParamId()];

    QSharedPointer<EventContext> context;

    if (bucket->execute()) {
        QNetworkReply *reply = executeRoute(networkManager, route);

        QByteArray response(reply->readAll());

        _logger->trace("Discord API Response: " + response);

        updateBucket(bucket, reply, response);

        context = QSharedPointer<EventContext>(new EventContext(response));

    } else {
        _logger->warning(QString("Rate limit reached for bucket: %1:%2. Limit resets at: %3")
                                .arg(bucket->getRateLimitBucket(),
                                     bucket->getMajorId(),
                                     QDateTime::fromSecsSinceEpoch(bucket->getRateLimitReset()).toString()));
    }

    return context;
}

void
HttpClient::updateBucket(QSharedPointer<Bucket> bucket, QNetworkReply *reply, const QByteArray &response) {
    QWriteLocker locker(bucket->getLock());

    if (!validStatusCode(reply, response)) {
        return;
    }

    qint64 rateLimitReset = reply->rawHeader(X_RATELIMIT_RESET).toUInt();

    if (rateLimitReset >= bucket->getRateLimitReset()) {
        bucket->setRateLimitReset(rateLimitReset);

        bucket->setRateLimitLimit(reply->rawHeader(X_RATELIMIT_LIMIT).toInt());

        bucket->setRateLimitRemaining(reply->rawHeader(X_RATELIMIT_REMAINING).toInt());
    }

    _logger->trace(QString("Rate Limit updated for bucket: %1:%2. Rate Limit reimaining: %3/%4. Rate limit resets at: %5")
                   .arg(bucket->getRateLimitBucket())
                   .arg(bucket->getMajorId())
                   .arg(bucket->getRateLimitRemaining())
                   .arg(bucket->getRateLimitLimit())
                   .arg(QDateTime::fromSecsSinceEpoch(bucket->getRateLimitReset()).toString()));
}

bool
HttpClient::validStatusCode(QNetworkReply *reply, const QByteArray &response) {
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    bool isValid = true;

    if (statusCode < 200 || (statusCode >= 300 && statusCode != 429)) {
        _logger->debug(QString("Discord API Call returned a problematic return code (%1): %2")
                        .arg(QString::number(statusCode), QString(response)));

        isValid = false;
    } else if (statusCode == 429) {
        RateLimit limit(response);

        if (limit.getGlobal().toBool()) {
            int resetAfter = qCeil(limit.getRetryAfter().toDouble());

            _globalRequestResetAt = QDateTime::currentSecsSinceEpoch() + resetAfter;
        }

        isValid = false;
    }

    return isValid;
}

QSharedPointer<EventContext>
HttpClient::createBucketAndExecute(QNetworkAccessManager &networkManager, Route &route) {
    QSharedPointer<EventContext> context;

    QNetworkReply *reply = executeRoute(networkManager, route);

    if (!reply) {
        return context;
    }

    QByteArray response = reply->readAll();

    if (!validStatusCode(reply, response)) {
        return context;
    }

    context = QSharedPointer<EventContext>(new EventContext(response));    

    createBucket(reply, route);

    return context;
}

void
HttpClient::createBucket(QNetworkReply *reply, Route &route) {
    QString rateLimitBucket;

    QString majorParamId;

    if(reply->hasRawHeader(X_RATELIMIT_BUCKET)) {
        rateLimitBucket = QString(reply->rawHeader(X_RATELIMIT_BUCKET));

        majorParamId = route.getMajorParamId();

    } else {
        rateLimitBucket = GLOBAL_BUCKET;

        majorParamId = GLOBAL_BUCKET;
    }

    if (!_bucketMaps.contains(rateLimitBucket)) {
        QMap<QString, QSharedPointer<Bucket> > bucketMap;

        bucketMap[majorParamId] = createNewBucket(majorParamId, rateLimitBucket, reply);

        _bucketMaps[rateLimitBucket] = bucketMap;

    } else if (!_bucketMaps[rateLimitBucket].contains(majorParamId)) {
        _bucketMaps[rateLimitBucket][majorParamId] = createNewBucket(majorParamId, rateLimitBucket, reply);
    }

    _bucketIdByRoute[route.getRouteWithMethod()] = rateLimitBucket;
}

bool
HttpClient::isGlobalLimitActive() const {
    if (QDateTime::currentSecsSinceEpoch() < _globalRequestResetAt) {
        _logger->warning(QString("You are being globally rate limited, reset at: %1")
                         .arg(QDateTime::fromSecsSinceEpoch(_globalRequestResetAt).toString()));

        return true;
    }

    return false;
}

QSharedPointer<Bucket>
HttpClient::createNewBucket(const QString &majorId, const QString &rateLimitBucket, QNetworkReply *reply) {
    QSharedPointer<Bucket> bucket = QSharedPointer<Bucket>(new Bucket(majorId, rateLimitBucket));

    bucket->setRateLimitRemaining(reply->rawHeader(X_RATELIMIT_REMAINING).toInt());

    bucket->setRateLimitLimit(reply->rawHeader(X_RATELIMIT_LIMIT).toInt());

    bucket->setRateLimitReset(reply->rawHeader(X_RATELIMIT_RESET).toUInt());

    _logger->trace(QString("Bucket created for: %1:%2. Rate Limit reimaining: %3/%4. Rate limit resets at: %5")
                   .arg(bucket->getRateLimitBucket())
                   .arg(bucket->getMajorId())
                   .arg(bucket->getRateLimitRemaining())
                   .arg(bucket->getRateLimitLimit())
                   .arg(QDateTime::fromSecsSinceEpoch(bucket->getRateLimitReset()).toString()));

    return bucket;
}

QNetworkReply*
HttpClient::executeRoute(QNetworkAccessManager &networkManager, Route &route) {
    if (isGlobalLimitActive()) {
        return nullptr;
    }

    QNetworkReply *reply;

    route.addRawHeader(_botAuthHeaderName, _botAuthHeaderValue);

    switch (route.getType()) {
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

    return reply;
}

void
HttpClient::waitForReply(QNetworkReply *reply) {
    QEventLoop loop;

    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();
}
