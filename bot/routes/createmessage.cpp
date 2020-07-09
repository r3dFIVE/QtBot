#include "createmessage.h"

const QString Route::PATH = "/channels/{channel.id}/messages";

QNetworkRequest
CreateMessage::request() {
 return QNetworkRequest();
}



QByteArray
CreateMessage::data() {
    return _message.toByteArray();
}
