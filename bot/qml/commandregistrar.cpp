#include "commandregistrar.h"

CommandRegistrar::CommandRegistrar() {

}

void
CommandRegistrar::setRegistry(const QMap<QString, QPair<QString, QSharedPointer<ICommand> > > &registry) {
    _registry = registry;
}

ICommand::CommandMapping
CommandRegistrar::getCommand(const QString &command) {
    if (_registry.contains(command)) {
        return _registry[command];
    } else {
        return QPair<QString, QSharedPointer<ICommand>>();
    }
}
