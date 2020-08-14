#ifndef GATEWAYBINDING_H
#define GATEWAYBINDING_H

#include "ibinding.h"
#include "util/globals.h"

class GatewayBinding : public IBinding
{

    QString _eventName;

public:

    static const QString GATEWAY_EVENT;

    GatewayBinding() {}
    GatewayBinding(const QString &eventType);
    GatewayBinding(const GatewayBinding &other);

    GatewayBinding &operator=(const GatewayBinding &other);

    QString getEventName() const;
    void setEventName(const QString &eventType);

    bool isValid(const QMetaObject &metaObject) const override;
};

#endif // GATEWAYBINDING_H
