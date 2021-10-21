#include "idbmanager.h"

const QString IDBManager::COMMAND_RESTRICTIONS = "COMMAND_RESTRICTIONS";

void
IDBManager::notImplemented(QString name) {
    _logger->trace(QString("%1 is not currently implement for given database type.").arg(name));
}
