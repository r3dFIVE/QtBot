/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QObject>
#include <QMutex>
#include <QReadWriteLock>

#include "logging/logfactory.h"
#include "routes/route.h"
#include "payloads/eventcontext.h"
#include "util/settings.h"
#include "bucket.h"


class HttpClient : public QObject
{
    Q_OBJECT

    Logger *_logger;

    static const QByteArray X_RATELIMIT_GLOBAL;
    static const QByteArray X_RATELIMIT_RESET;
    static const QByteArray X_RATELIMIT_REMAINING;
    static const QByteArray X_RATELIMIT_LIMIT;
    static const QByteArray X_RATELIMIT_BUCKET;

    static qint64 _globalRequestResetAt;
    static QMap<QString, QString> _bucketIdByRoute;
    static QMap<QString, QMap<QString, QSharedPointer<Bucket> > > _bucketMaps;
    static QReadWriteLock _discoveryLock;

    QByteArray _botAuthHeaderName;
    QByteArray _botAuthHeaderValue;

    bool validStatusCode(QNetworkReply *reply, const QByteArray &repsonse);
    bool isGlobalLimitActive() const;

    QSharedPointer<EventContext> createBucketAndExecute(QNetworkAccessManager &networkManager, Route &route);
    QSharedPointer<EventContext> checkBucketAndExecute(QNetworkAccessManager &networkManager, Route &route);
    QNetworkReply* executeRoute(QNetworkAccessManager &networkManager, Route &route);
    QSharedPointer<Bucket> createNewBucket(const QString &majorId, const QString &rateLimitBucket, QNetworkReply *reply);

    void addAuthHeader(Route &route);
    void createBucket(QNetworkReply *reply, Route &route);
    void updateBucket(QSharedPointer<Bucket> bucket, QNetworkReply *reply, const QByteArray &response);
    void waitForReply(QNetworkReply *reply);

public:
    HttpClient(const QString &botToken);
    QSharedPointer<EventContext> processRoute(Route &route);

};

#endif // HTTPCLIENT_H
