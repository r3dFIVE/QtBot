#ifndef BINDINGFACTORY_H
#define BINDINGFACTORY_H

#include "commandbinding.h"
#include "gatewaybinding.h"
#include "timedbinding.h"

#include <QObject>

class BindingFactory : public QObject
{
    Q_OBJECT

public:
    BindingFactory(QObject *parent = nullptr) = delete;
    BindingFactory(const BindingFactory &other) = delete;

    static TimedBinding createTimedBinding(BotScript *botScript, const QJsonValue &binding);
    static GatewayBinding createGatewayBinding(BotScript *botScript, const QJsonValue &binding);
    static CommandBinding createCommandBinding(BotScript *botScript, const QJsonValue &binding);

signals:

};

#endif // BINDINGFACTORY_H
