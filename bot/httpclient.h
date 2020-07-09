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

public:
    HttpClient(const QString &botToken);
    void post(const Message &message, QString quote);
signals:

public slots:
    void processResponse(QNetworkReply *reply);

};

#endif // HTTPCLIENT_H
