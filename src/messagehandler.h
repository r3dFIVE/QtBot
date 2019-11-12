#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include "payloads/gatewaypayload.h"

#include "gatewayconnection.h"

class MessageHandler : public QObject
{
    Q_OBJECT

public:
    MessageHandler(const GatewayConnection* connection, QObject *parent = nullptr);

private Q_SLOTS:
    void processPayload(GatewayPayload payload);
};

#endif // MESSAGEHANDLER_H
