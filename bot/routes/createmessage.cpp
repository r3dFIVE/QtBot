#include "createmessage.h"


QNetworkRequest
CreateMessage::request() {
 return QNetworkRequest();
}



QByteArray
CreateMessage::data()
{
    return _message.toByteArray();
}
