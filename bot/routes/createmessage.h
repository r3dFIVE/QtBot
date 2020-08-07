#ifndef CREATEMESSAGE_H
#define CREATEMESSAGE_H

#include <QObject>

#include "route.h"
#include "payloads/eventcontext.h"



class CreateMessage : public Route
{
    Q_OBJECT

public:

    CreateMessage() {};
    CreateMessage(const CreateMessage &other) { Q_UNUSED(other) }
    CreateMessage(const EventContext &context);
    ~CreateMessage() {}

    virtual QNetworkRequest request() override;
    virtual QByteArray payload() override;
};

Q_DECLARE_METATYPE(CreateMessage)

#endif // CREATEMESSAGE_H
