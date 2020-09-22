#ifndef CREATEMESSAGE_H
#define CREATEMESSAGE_H

#include <QObject>

#include "route.h"
#include "payloads/eventcontext.h"



class ChannelCreateMessage : public Route
{
    Q_OBJECT

public:

    ChannelCreateMessage() {};
    ChannelCreateMessage(const ChannelCreateMessage &other) { Q_UNUSED(other) }
    ChannelCreateMessage(const EventContext &context);
    ~ChannelCreateMessage() {}

    virtual QNetworkRequest request() override;
    virtual QByteArray payload() override;
};

Q_DECLARE_METATYPE(ChannelCreateMessage)

#endif // CREATEMESSAGE_H
