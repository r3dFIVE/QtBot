#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include "payloads/gatewaypayload.h"


class EventHandler : public QObject
{
    Q_OBJECT

public slots:
    void processEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload);
};

#endif // MESSAGEHANDLER_H
