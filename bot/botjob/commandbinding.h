#ifndef COMMANDBINDING_H
#define COMMANDBINDING_H

#include "ibinding.h"

class CommandBinding : public IBinding
{

    QString _commandName;

public:
    static const QString COMMAND;

    CommandBinding() { }
    CommandBinding(const QString &commandName, const IBotJob::FunctionMapping &functionMapping);
    CommandBinding(const CommandBinding &other);
    ~CommandBinding() {}

    CommandBinding &operator=(const CommandBinding &other);

    QString getCommandName() const;
    void setCommandName(const QString &commandName);

    bool isValid(const QMetaObject &metaObject) const override;
};

#endif // COMMANDBINDING_H
