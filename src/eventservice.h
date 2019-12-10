#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include "payloads/gatewaypayload.h"

#include "gatewayservice.h"

class EventService : public QObject
{
    Q_OBJECT

public:
    EventService(QObject *parent = nullptr);

public slots:
    void processEvent(QSharedPointer<GatewayPayload> payload);


};

#endif // MESSAGEHANDLER_H
