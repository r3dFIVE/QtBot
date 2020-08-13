#include "commandbinding.h"

#include <QMetaProperty>

const QString CommandBinding::COMMAND = "command";


CommandBinding::CommandBinding(const QString &commandName, const IBotJob::FunctionMapping &functionMapping) {
    _commandName = commandName;

    _functionMapping = functionMapping;
}

CommandBinding::CommandBinding(const CommandBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _commandName = other._commandName;
}

CommandBinding
&CommandBinding::operator=(const CommandBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _commandName = other._commandName;

    return *this;
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
    if (_functionMapping.first.isEmpty() || _functionMapping.second.isNull()) {
        _logger->warning(QString("Invalid command mapping. First: %1, Second: %2... Discarding binding.")
                         .arg(_functionMapping.first.isEmpty() )
                         .arg(_functionMapping.second.isNull() ? "nullptr" : _functionMapping.second->objectName()));
    }

    if (_commandName.isEmpty()) {
        _logger->warning(QString("\"%1\" property is not set for command binding for function \"%2\"... Discarding binding.")
                         .arg(COMMAND)
                         .arg(_functionMapping.first));

        return false;
    }

    QByteArray functionName = buildFunctionSearchString();

    if (metaObject.indexOfMethod(functionName) < 0) {
        _logger->warning(QString("\"%1\" property is not set for command binding for function \"%2\"... Discarding binding.")
                         .arg(COMMAND)
                         .arg(_functionMapping.first));

        return false;
    }

    return true;
}
