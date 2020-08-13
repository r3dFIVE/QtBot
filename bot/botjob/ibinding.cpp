#include "ibinding.h"

#include "util/enumutils.h"


const QString IBinding::BINDING_TYPE = "binding_type";
const QString IBinding::FUNCTION = "function";
const QString IBinding::GATEWAY_EVENT = "gateway_event";
const QString IBinding::REPEAT_AFTER = "repeat_after";

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

QByteArray
IBinding::buildFunctionSearchString() const {
    return _functionMapping.first.toUtf8() + "(QVariant)";
}
