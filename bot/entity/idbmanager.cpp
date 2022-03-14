#include "idbmanager.h"

const QString IDBManager::COMMAND_RESTRICTIONS = "COMMAND_RESTRICTIONS";

IDBManager::IDBManager(QObject *parent) : QObject (parent) {
    if (parent) {
        _logger = LogFactory::getLogger(parent);
    } else {
        _logger = LogFactory::getLogger(this);
    }
}

void
IDBManager::notImplemented(QString name) {
    _logger->trace(QString("%1 is not currently implement for given database type.").arg(name));
}
