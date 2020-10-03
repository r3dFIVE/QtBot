#include "commandbinding.h"


const QString CommandBinding::COMMAND = "command";
const QString CommandBinding::ADMIN_ONLY = "admin_only";

CommandBinding::CommandBinding(const QString &commandName, const IBotJob::FunctionMapping &functionMapping) {
    _commandName = commandName;

    _functionMapping = functionMapping;
}

CommandBinding::CommandBinding(const CommandBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _commandName = other._commandName;

    _adminOnly = other._adminOnly;
}

CommandBinding
&CommandBinding::operator=(const CommandBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _commandName = other._commandName;

    _adminOnly = other._adminOnly;

    return *this;
}

bool
CommandBinding::isAdminOnly() const {
    return _adminOnly;
}

void
CommandBinding::setAdminOnly(const bool adminOnly) {
    _adminOnly = adminOnly;
}

QString
CommandBinding::getCommandName() const {
    return _commandName;
}

void
CommandBinding::setCommandName(const QString &commandName) {
    _commandName = commandName;
}

bool
CommandBinding::isValid(const QMetaObject &metaObject) const {
    if (!validateFunctionMapping(metaObject)) {
        return false;
    }

    if (_commandName.isEmpty()) {
        _logger->warning(QString("\"%1\" property is not set for command binding for function \"%2\"... Discarding binding.")
                         .arg(COMMAND)
                         .arg(_functionMapping.first));

        return false;
    }

    return true;
}
