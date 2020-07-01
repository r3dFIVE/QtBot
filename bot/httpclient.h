#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "util/settings.h"
#include "routes/route.h"

#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QObject>


class HttpClient : public QObject
{
    Q_OBJECT

    QString _botToken;
    QSharedPointer<QNetworkAccessManager> _networkManager;

public:
    HttpClient(QSharedPointer<Settings> settings);
    void post(const Message &message, QString quote);
signals:

};

#endif // HTTPCLIENT_H
