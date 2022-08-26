#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <QEventLoop>
#include <QNetworkReply>
#include <QObject>


class HttpUtils : public QObject {
    Q_OBJECT
public:
    static void waitForReply(QSharedPointer<QNetworkReply> reply, const bool ignoreSslErrors = false);

public slots:
    void ignoreSslErrors();
};

#endif // HTTPUTILS_H
