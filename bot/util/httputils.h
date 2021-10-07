#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <QEventLoop>
#include <QNetworkReply>
#include <QObject>


class HttpUtils : public QObject {
    Q_OBJECT
    static QString _botToken;
public:
    static QString botToken();
    static void setBotToken(const QString &token);
    static void waitForReply(QSharedPointer<QNetworkReply> reply, const bool ignoreSslErrors = false);

public slots:
    void ignoreSslErrors();
};

#endif // HTTPUTILS_H
