#include "ibinding.h"


const QString IBinding::BINDING_TYPE = "binding_type";
const QString IBinding::BINDING_TYPE_COMMAND = "command";
const QString IBinding::BINDING_TYPE_GATEWAY = "gateway";
const QString IBinding::BINDING_TYPE_TIMED = "timed";
const QString IBinding::FUNCTION = "function";
const QString IBinding::DESCRIPTION = "description";

bool IBinding::validateFunctionMapping(const QMetaObject &metaObject) const {
    if (_functionMapping.first.isEmpty() || !_functionMapping.second) {
        _logger->warning(QString("Invalid command mapping. First: %1, Second: %2... Discarding binding.")
                         .arg(_functionMapping.first.isEmpty() )
                         .arg(!_functionMapping.second ? "nullptr" : _functionMapping.second->objectName()));

        return false;
    }

    QByteArray functionName = QString(_functionMapping.first + "(QVariant)").toUtf8();

    if (metaObject.indexOfMethod(functionName) < 0) {
        _logger->warning(QString("\"%1\" function was not defined in this script... Discarding binding.")
                         .arg(_functionMapping.first));

        return false;
    }

    return true;
}

IBotJob::FunctionMapping
IBinding::getFunctionMapping() const {
    return _functionMapping;
}

QString
IBinding::getDescription() const {
    return _description;
}

void
IBinding::setDescription(const QString &description) {
    _description = description;
}

void
IBinding::setFunctionMapping(const IBotJob::FunctionMapping &functionMapping) {
    _functionMapping = functionMapping;
}
