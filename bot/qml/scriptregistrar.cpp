#include "scriptregistrar.h"

ScriptRegistrar::ScriptRegistrar(QObject *parent) : QObject(parent)
{

}

void
ScriptRegistrar::setRegistry(const QMap<QString, QPair<QString, QSharedPointer<BotScript> > > &registry) {
    _registry = registry;
}

BotMapping
ScriptRegistrar::getScript(const QString &command) {
    if (_registry.contains(command)) {
        return _registry[command];
    } else {
        return QPair<QString, QSharedPointer<BotScript>>();
    }
}
