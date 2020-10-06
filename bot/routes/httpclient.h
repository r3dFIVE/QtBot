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
