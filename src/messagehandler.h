#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include "payloads/gatewaypayload.h"

class MessageHandler
{
public:
    MessageHandler();

public slots:
    void processPayload(GatewayPayload payload);
};

#endif // MESSAGEHANDLER_H
