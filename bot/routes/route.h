#ifndef ROUTE_H
#define ROUTE_H

#include "payloads/jsonserializable.h"
#include "payloads/message.h"

#include <QNetworkRequest>
#include <QObject>


class Route : public QObject
{
    Q_OBJECT

    QSharedPointer<Message> _payload =
            QSharedPointer<Message>(new Message);

public:

    typedef enum RequestType {
        POST,       // C
        GET,        // R
        PUT,        // U (Update/Replace)
        PATCH,      // U (Update/Modify)
        DELETE,     // D
    } RequestType;
    Q_ENUM(RequestType);

    RequestType _requestType;

    virtual QNetworkRequest request() = 0;
    virtual QByteArray data() = 0;
};

Q_DECLARE_METATYPE(Route*)

#endif // ROUTE_H
