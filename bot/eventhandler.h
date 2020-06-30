#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include <util/settings.h>

#include "util/function.h"
#include "payloads/gatewaypayload.h"


class EventHandler : public QObject
{
    Q_OBJECT

    QMap<QString, Function<void(const QString &args)> > commands;
    //bool isRegisteredCommand(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void execute(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    QString parseCommandToken(QString message);
    void processDispatch(QSharedPointer<GatewayPayload::GatewayPayload> payload);
public:
    EventHandler(QSharedPointer<Settings> settings);

public slots:    
    void processEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload);

};

#endif // MESSAGEHANDLER_H
