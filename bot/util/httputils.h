#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <QEventLoop>
#include <QNetworkReply>
#include <QObject>


class HttpUtils {
    static QString _botToken;
public:
    static QString botToken();
    static void setBotToken(const QString &token);
    static void waitForReply(QSharedPointer<QNetworkReply> reply);
};

#endif // HTTPUTILS_H
