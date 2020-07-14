#ifndef DISCORDAPI_H
#define DISCORDAPI_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "httpclient.h"


class DiscordAPI : public QObject
{
    Q_OBJECT

    HttpClient _httpClient;

public:
    DiscordAPI(const QString &botToken) : _httpClient(botToken) {}
    ~DiscordAPI() {}

    /*
     *      CHANNEL API FUNCTIONS
     *      https://discord.com/developers/docs/resources/channel
     */

    QSharedPointer<EventContext> channelCreateMessage(QSharedPointer<EventContext> context);
};

#endif // DISCORDAPI_H
