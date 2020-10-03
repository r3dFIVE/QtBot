#ifndef COMMANDBINDING_H
#define COMMANDBINDING_H

#include "ibinding.h"

class CommandBinding : public IBinding
{

    bool _adminOnly = false;
    QString _commandName;


public:
    static const QString COMMAND;
    static const QString ADMIN_ONLY;

    CommandBinding() { }
    CommandBinding(const QString &commandName, const IBotJob::FunctionMapping &functionMapping);
    CommandBinding(const CommandBinding &other);
    ~CommandBinding() {}

    CommandBinding &operator=(const CommandBinding &other);

    bool isAdminOnly() const;
    QString getCommandName() const;
    void setAdminOnly(const bool adminOnly);
    void setCommandName(const QString &commandName);

    bool isValid(const QMetaObject &metaObject) const override;
};

#endif // COMMANDBINDING_H
