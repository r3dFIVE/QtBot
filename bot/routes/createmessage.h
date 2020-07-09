#ifndef CREATEMESSAGE_H
#define CREATEMESSAGE_H

#include "route.h"

#include <QObject>


class CreateMessage : public Route
{
    Q_OBJECT

    Message _message;
public:


    virtual QNetworkRequest request() override;
    virtual QByteArray data() override;


    CreateMessage() {}
    ~CreateMessage() {}
};

Q_DECLARE_METATYPE(CreateMessage)

#endif // CREATEMESSAGE_H
