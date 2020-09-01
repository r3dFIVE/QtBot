#include "timedbinding.h"


const QString TimedBinding::REPEAT_AFTER = "repeat_after";
const QString TimedBinding::SINGLE_SHOT = "single_shot";
const QString TimedBinding::SINGLETON = "singleton";
const QString TimedBinding::SOURCE_PAYLOAD = "source_payload";

TimedBinding::TimedBinding(const TimedBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _singleShot = other._singleShot;

    _repeatAfter = other._repeatAfter;

    _scriptName = other._scriptName;

    _sourcePayload = other._sourcePayload;

    _registeredAt = other._registeredAt;
}

TimedBinding
&TimedBinding::operator=(const TimedBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _singleShot = other._singleShot;

    _repeatAfter = other._repeatAfter;

    _scriptName = other._scriptName;

    _sourcePayload = other._sourcePayload;

    _registeredAt = other._registeredAt;

    return *this;
}

QString
TimedBinding::getScriptName() const {
    return _scriptName;
}

void
TimedBinding::setScriptName(const QString &scriptName) {
    _scriptName = scriptName;
}

qint64
TimedBinding::getRepeatAfter() const {
    return _repeatAfter;
}

void
TimedBinding::setRepeatAfter(int repeatAfter) {
    _repeatAfter = repeatAfter;
}

bool
TimedBinding::isSingleShot() const {
    return _singleShot;
}

void
TimedBinding::setSingleShot(bool singleShot) {
    _singleShot = singleShot;
}

QJsonValue
TimedBinding::getSourcePayload() const {
    return _sourcePayload;
}

void
TimedBinding::setSourcePayload(const QJsonValue &sourcePayload) {
    _sourcePayload = sourcePayload;
}

qint64
TimedBinding::getRegsteredAt() const {
    return _registeredAt;
}

void
TimedBinding::setRegisteredAt(const qint64 registeredAt) {
    _registeredAt = registeredAt;
}


bool
TimedBinding::isValid(const QMetaObject &metaObject) const {
    if (!validateFunctionMapping(metaObject)) {
        return false;
    }

    if (_scriptName.isEmpty()) {
        _logger->warning("Script name not set for timed event... Discarding binding.");

        return false;
    }

    if (_repeatAfter <= 0) {
        _logger->warning("Repeat after value must be set and greater than 0... Discarding binding.");

        return false;
    }

    return true;
}
