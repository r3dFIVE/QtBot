#include "httpclient.h"
#include "util/globals.h"

#include <QNetworkAccessManager>


HttpClient::HttpClient(QSharedPointer<Settings> settings)
{
    _networkManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager(this));
    _botToken = settings->value(SettingsParam::Connection::BOT_TOKEN).toString();
}

void
HttpClient::post(const Message &message, QString quote) {
    QString url = QString("https://discord.com/api/channels/%1/messages").arg(message.getChannelId().toString());
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("User-Agent", "QtBot 0.3");
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bot %1").arg(_botToken).toUtf8());
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    Message payload;
    payload.setContent(quote);
    _networkManager->post(request, payload.toByteArray());
}
