#include "bindingfactory.h"

void
BindingFactory::build(TimedBinding &timedBinding, BotScript *botScript, const QJsonValue &binding) {
    timedBinding.setId(QUuid::createUuid().toString(QUuid::Id128));

    timedBinding.setFunctionMapping(qMakePair(binding[TimedBinding::FUNCTION].toString(), botScript));

    timedBinding.setEventContext(binding[TimedBinding::CONTEXT].toObject());

    QSharedPointer<TimedBindingProperties> properties = QSharedPointer<TimedBindingProperties>(new TimedBindingProperties);

    properties->scriptName = botScript->getName();

    properties->fireAfter = binding[TimedBinding::FIRE_AFTER].toInt();

    if (binding[TimedBinding::SINGLE_SHOT].isBool()) {
        properties->singleShot = binding[TimedBinding::SINGLE_SHOT].toBool();
    }

    if (binding[TimedBinding::SINGLETON].isBool()) {
        properties->singleton =binding[TimedBinding::SINGLETON].toBool();
    }

    if (binding[TimedBinding::FORCE_ENABLE].isBool()) {
        properties->forceEnable = binding[TimedBinding::FORCE_ENABLE].toBool();
    }

    timedBinding.setBaseProperties(buildBaseProperties(binding));

    timedBinding.setTimedProperties(properties);
}

QSharedPointer<IBindingProperties>
BindingFactory::buildBaseProperties(const QJsonValue &binding) {
    QSharedPointer<IBindingProperties> properties = QSharedPointer<IBindingProperties>(new IBindingProperties);

    properties->name = binding[IBinding::BINDING_NAME].toString();

    properties->description = binding[IBinding::DESCRIPTION].toString();

    properties->descriptionShort = binding[IBinding::DESCRIPTION_SHORT].toString();

    if (binding[IBinding::IGNORE_ADMIN].isBool()) {
        properties->ignoreAdmin = binding[IBinding::IGNORE_ADMIN].toBool();
    }

    if (binding[IBinding::ADMIN_ONLY].isBool()) {
        properties->adminOnly =binding[IBinding::ADMIN_ONLY].toBool();
    }

    return properties;
}

void
BindingFactory::build(GatewayBinding &gatewayBinding, BotScript *botScript, const QJsonValue &binding) {
    gatewayBinding.setFunctionMapping(qMakePair(binding[GatewayBinding::FUNCTION].toString(), botScript));

    QSharedPointer<GatewayBindingProperties> properties = QSharedPointer<GatewayBindingProperties>(new GatewayBindingProperties);

    properties->eventName = binding[GatewayBinding::GATEWAY_EVENT].toString();

    gatewayBinding.setBaseProperties(buildBaseProperties(binding));

    gatewayBinding.setGatewayProperties(properties);
}

void
BindingFactory::build(CommandBinding &commandBinding, BotScript *botScript, const QJsonValue &binding) {
    commandBinding.setFunctionMapping(qMakePair(binding[CommandBinding::FUNCTION].toString(), botScript));

    QSharedPointer<IBindingProperties> base = buildBaseProperties(binding);

    base->name = binding[CommandBinding::COMMAND].toString();

    commandBinding.setBaseProperties(base);
}

