#include "corecommand.h"

bool
CoreCommand::invokable() {
    bool canLock = _runLock.tryLock();

    if (canLock) {
        _runLock.unlock();
    }

    return !canLock;
}

void
CoreCommand::execute(const QByteArray &command, const EventContext &context) {
    QMutexLocker lock(&_runLock);

    LogFactory::getLogger()->trace(QString("Executing core command: %1").arg(QString(command)));

    _command(context);
}
