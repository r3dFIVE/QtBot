#include "imanager.h"

const QString IManager::COMMAND_RESTRICTIONS = "COMMAND_RESTRICTIONS";

void
IManager::notImplemented(QString name) {
    _logger->trace(QString("%1 is not currently implement for given database type.").arg(name));
}

void
IManager::saveEvent(QSharedPointer<GatewayPayload> payload) {
    notImplemented("saveEvent");
}
