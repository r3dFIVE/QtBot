#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include "payloads/gatewaypayload.h"

#include "gateway.h"

class EventHandler : public QObject
{
    Q_OBJECT

public:
    EventHandler(QObject *parent = nullptr);

public slots:
    void processEvent(QSharedPointer<GatewayPayload> payload);


};

#endif // MESSAGEHANDLER_H
