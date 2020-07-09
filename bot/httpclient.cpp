#include "httpclient.h"
#include "util/globals.h"
#include "routes/createmessage.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>


HttpClient::HttpClient(const QString &botToken)
{
    _botToken = botToken;
}

void
HttpClient::processResponse(QNetworkReply *reply) {
    qDebug() << reply->readAll();
}

void
HttpClient::post(const Message &message, QString quote) {
    QNetworkAccessManager networkMananger;
    QString url = QString("https://discord.com/api/channels/%1/messages").arg(message.getChannelId().toString());
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("User-Agent", "QtBot 0.3");
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bot %1").arg(_botToken).toUtf8());
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    Message payload;
    payload.setContent(quote);





    QNetworkReply *reply = networkMananger.post(request, payload.toByteArray());

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    qDebug() << reply->readAll();
}
