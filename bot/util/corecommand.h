#ifndef CORECOMMAND_H
#define CORECOMMAND_H

#include "icommand.h"
#include "logging/logfactory.h"
#include "payloads/message.h"

#include <functional>



class CoreCommand : public QObject, public ICommand {
    Q_OBJECT

    std::function<void(const Message &message)> _command;

public:
    CoreCommand() {}
    CoreCommand(std::function<void(const Message &message)> command) { _command = command; }
    CoreCommand(const CoreCommand &other) { Q_UNUSED(other) }
    ~CoreCommand() {}

    void execute(const QByteArray &command, const Message &message) override {
        LogFactory::getLogger()->trace(QString("Executing core command: %1").arg(QString(command)));

        _command(message);
    }
};


#endif // CORECOMMAND_H
