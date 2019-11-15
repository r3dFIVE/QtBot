#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include "payloads/gatewaypayload.h"

#include "gatewayconnection.h"

class MessageHandler : public QObject
{
    Q_OBJECT

public:
    MessageHandler(QObject *parent = nullptr);

public slots:
    void processPayload(int payload);

signals:
    void updateHeartbeat(int heartbeatInterval);

private:
    void processHello(GatewayPayload payload);
};

#endif // MESSAGEHANDLER_H
