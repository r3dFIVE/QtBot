#ifndef BINDINGFACTORY_H
#define BINDINGFACTORY_H

#include "commandbinding.h"
#include "gatewaybinding.h"
#include "timedbinding.h"

#include <QObject>

class BindingFactory : public QObject
{
    Q_OBJECT

    static Logger *LOGGER;

public:
    BindingFactory(QObject *parent = nullptr) = delete;
    BindingFactory(const BindingFactory &other) = delete;

    static void build(TimedBinding &timedBinding, BotScript *botScript, const QJsonValue &binding);
    static void build(GatewayBinding &gatewayBinding, BotScript *botScript, const QJsonValue &binding);
    static void build(CommandBinding &commandBinding, BotScript *botScript, const QJsonValue &binding);

    static bool validateTimedBinding(BotScript *botScript, const QJsonValue &binding, const QString &fileName);
signals:

};

#endif // BINDINGFACTORY_H
