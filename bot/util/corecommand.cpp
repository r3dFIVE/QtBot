#include "corecommand.h"

bool
CoreCommand::running() {
    return _runLock.tryLock();
}

void
CoreCommand::execute(const QByteArray &command, const EventContext &context) {
    QMutexLocker lock(&_runLock);

    LogFactory::getLogger()->trace(QString("Executing core command: %1").arg(QString(command)));

    _command(context);
}
