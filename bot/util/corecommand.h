#ifndef CORECOMMAND_H
#define CORECOMMAND_H

#include <functional>

#include "botjob/ibotjob.h"
#include "logging/logfactory.h"
#include "payloads/message.h"

class CoreCommand : public QObject, public IBotJob {
    Q_OBJECT

    std::function<void(const EventContext &context)> _command;

    QMutex _runLock;

public:
    CoreCommand() {}
    CoreCommand(std::function<void(const EventContext &context)> command) { _command = command; }
    CoreCommand(const CoreCommand &other) { Q_UNUSED(other) }
    ~CoreCommand() {}

    bool invokable() override;
    void execute(const QByteArray &command, const EventContext &context) override;

};


#endif // CORECOMMAND_H
