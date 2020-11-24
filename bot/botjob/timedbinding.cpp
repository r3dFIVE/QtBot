/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "timedbinding.h"


const QString TimedBinding::CONTEXT = "context";
const QString TimedBinding::FIRE_AFTER = "fire_after";
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

    _fireAfter = other._fireAfter;

    _scriptName = other._scriptName;

    _eventContext = other._eventContext;

    _startedAt = other._startedAt;

    _remainder = other._remainder;

    _running = other._running;

    _stoppedAt = other._stoppedAt;

    _id = other._id;
}

TimedBinding
&TimedBinding::operator=(const TimedBinding &other) {
    _functionMapping = other._functionMapping;

    _logger = other._logger;

    _description = other._description;

    _singleShot = other._singleShot;

    _fireAfter = other._fireAfter;

    _scriptName = other._scriptName;

    _eventContext = other._eventContext;

    _startedAt = other._startedAt;

    _remainder = other._remainder;

    _running = other._running;

    _stoppedAt = other._stoppedAt;

    _id = other._id;

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
TimedBinding::getFireAfter() const {
    return _fireAfter;
}

void
TimedBinding::setFireAfter(int fireAfter) {
    _fireAfter = fireAfter;
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

    _remainder = _fireAfter - (_stoppedAt - _startedAt);

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
TimedBinding::getRemaining() {
    if (_remainder) {
        if (_stoppedAt) {
            return _remainder;
        } else {
            return (_remainder - (QDateTime::currentSecsSinceEpoch() - _startedAt));
        }
    } else {
        return (_fireAfter - (QDateTime::currentSecsSinceEpoch() - _startedAt));
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

QString
TimedBinding::id() const {
    return _id;
}

void
TimedBinding::setId(const QString &id) {
    _id = id;
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

    if (_fireAfter <= 0) {
        _logger->warning("fire_after value must be set and greater than 0... Discarding binding.");

        return false;
    }

    return true;
}
