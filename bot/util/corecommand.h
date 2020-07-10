#ifndef CORECOMMAND_H
#define CORECOMMAND_H

#include "icommand.h"
#include "logging/logfactory.h"
#include "payloads/message.h"

#include <functional>



class CoreCommand : public QObject, public ICommand {
    Q_OBJECT

    std::function<void(const EventContext &context)> _command;

public:
    CoreCommand() {}
    CoreCommand(std::function<void(const EventContext &context)> command) { _command = command; }
    CoreCommand(const CoreCommand &other) { Q_UNUSED(other) }
    ~CoreCommand() {}

    void execute(const QByteArray &command, const EventContext &context) override {
        LogFactory::getLogger()->trace(QString("Executing core command: %1").arg(QString(command)));

        _command(context);
    }
};


#endif // CORECOMMAND_H
