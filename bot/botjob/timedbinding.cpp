#include "timedbinding.h"


const QString TimedBinding::EVENT_CONTEXT = "event_context";
const QString TimedBinding::REPEAT_AFTER = "repeat_after";
const QString TimedBinding::SINGLE_SHOT = "single_shot";
const QString TimedBinding::SINGLETON = "singleton";

TimedBinding::TimedBinding() {
    _logger = LogFactory::getLogger();
}

TimedBinding::TimedBinding(const TimedBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _singleShot = other._singleShot;

    _repeatAfter = other._repeatAfter;

    _scriptName = other._scriptName;

    _eventContext = other._eventContext;

    _startedAt = other._startedAt;

    _remainder = other._remainder;

    _running = other._running;

    _stoppedAt = other._stoppedAt;
}

TimedBinding
&TimedBinding::operator=(const TimedBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _singleShot = other._singleShot;

    _repeatAfter = other._repeatAfter;

    _scriptName = other._scriptName;

    _eventContext = other._eventContext;

    _startedAt = other._startedAt;

    _remainder = other._remainder;

    _running = other._running;

    _stoppedAt = other._stoppedAt;

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

void
TimedBinding::resume() {
    _stoppedAt = 0;

    _startedAt = QDateTime::currentSecsSinceEpoch();

    _running = true;
}

void
TimedBinding::start() {
    _remainder = 0;

    _running = true;

    _startedAt = QDateTime::currentSecsSinceEpoch();

    _stoppedAt = 0;
}

void
TimedBinding::stop() {
    _stoppedAt = QDateTime::currentSecsSinceEpoch();

    _remainder = _repeatAfter - (_stoppedAt - _startedAt);

    _running = false;
}

bool
TimedBinding::isRunning() const {
    return _running;
}

bool
TimedBinding::isSingleShot() const {
    return _singleShot;
}

void
TimedBinding::setSingleShot(bool singleShot) {
    _singleShot = singleShot;
}

EventContext
TimedBinding::getEventContext() const {
    return _eventContext;
}

qint64
TimedBinding::getReimaining() {
    if (_remainder) {
        if (_stoppedAt) {
            return _remainder;
        } else {
            return (_remainder - (QDateTime::currentSecsSinceEpoch() - _startedAt));
        }
    } else {
        return (_repeatAfter - (QDateTime::currentSecsSinceEpoch() - _startedAt));
    }
}

void
TimedBinding::setEventContext(const EventContext &eventContext) {
    _eventContext = eventContext;
}

qint64
TimedBinding::getStartedAt() const {
    return _startedAt;
}

void
TimedBinding::setStartedAt(const qint64 startedAt) {
    _startedAt = startedAt;
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
