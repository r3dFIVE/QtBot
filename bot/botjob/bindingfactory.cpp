#include "bindingfactory.h"


TimedBinding
BindingFactory::createTimedBinding(BotScript *botScript, const QJsonValue &binding) {
    QString functionName = binding[IBinding::FUNCTION].toString();

    QString bindingName = binding[TimedBinding::BINDING_NAME].toString();

    TimedBinding timedBinding;

    timedBinding.setId(QUuid::createUuid().toString(QUuid::Id128));

    timedBinding.setFunctionMapping(qMakePair(functionName, botScript));

    timedBinding.setScriptName(botScript->getScriptName());

    timedBinding.setFireAfter(binding[TimedBinding::FIRE_AFTER].toInt());

    if (binding[TimedBinding::SINGLE_SHOT].isBool()) {
        timedBinding.setSingleShot(binding[TimedBinding::SINGLE_SHOT].toBool());
    }

    if (binding[TimedBinding::SINGLETON].isBool()) {
        timedBinding.setSingleton(binding[TimedBinding::SINGLETON].toBool());
    }

    timedBinding.setBindingName(bindingName);

    timedBinding.setEventContext(binding[TimedBinding::CONTEXT].toObject());

    timedBinding.setDescription(binding[TimedBinding::DESCRIPTION].toString());

    return timedBinding;
}

GatewayBinding
BindingFactory::createGatewayBinding(BotScript *botScript, const QJsonValue &binding) {
    QString bindingName = binding[GatewayBinding::BINDING_NAME].toString();

    QString gatewayEventName = binding[GatewayBinding::GATEWAY_EVENT].toString();

    QString functionName = binding[GatewayBinding::FUNCTION].toString();

    GatewayBinding gatewayBinding;

    gatewayBinding.setFunctionMapping(qMakePair(functionName, botScript));

    gatewayBinding.setEventName(gatewayEventName);

    gatewayBinding.setBindingName(bindingName);

    gatewayBinding.setDescription(binding[GatewayBinding::DESCRIPTION].toString());

    if (binding[GatewayBinding::IGNORE_ADMIN].isBool()) {
        gatewayBinding.setIgnoreAdmin(binding[GatewayBinding::IGNORE_ADMIN].toBool());
    }

    return gatewayBinding;
}

CommandBinding
BindingFactory::createCommandBinding(BotScript *botScript, const QJsonValue &binding) {
    CommandBinding commandBinding;

    QString command = binding[CommandBinding::COMMAND].toString();

    commandBinding.setCommandName(command);

    QString functionName = binding[CommandBinding::FUNCTION].toString();

    commandBinding.setFunctionMapping(qMakePair(functionName, botScript));

    commandBinding.setDescription(binding[CommandBinding::DESCRIPTION].toString());

    if (binding[CommandBinding::ADMIN_ONLY].isBool()) {
        commandBinding.setAdminOnly(binding[CommandBinding::ADMIN_ONLY].toBool());
    }

    if (binding[CommandBinding::IGNORE_ADMIN].isBool()) {
        commandBinding.setIgnoreAdmin(binding[CommandBinding::IGNORE_ADMIN].toBool());
    }

    return commandBinding;
}

