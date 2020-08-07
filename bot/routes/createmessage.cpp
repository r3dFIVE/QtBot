#include "createmessage.h"

#include "util/serializationutils.h"


const Route::Bucket Route::BUCKET = CHANNEL_ID;
const Route::RequestType Route::REQUEST_TYPE = POST;
const QString Route::PATH = "/channels/{channel.id}/messages";

CreateMessage::CreateMessage(const EventContext &context) {
    QString path = QString("%1%2").arg(Route::DISCORD_API_PATH).arg(PATH);

    path.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

    buildRequest(path);

    _payload = SerializationUtils::toQByteArray(context.getTargetPayload());
}

QNetworkRequest
CreateMessage::request() {
    return _request;
}

QByteArray
CreateMessage::payload() {
    return _payload;
}

