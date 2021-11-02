/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "timedjobs.h"


bool
TimedJobs::hasJobs() const {
    return !_timedBindings.isEmpty();
}

QList<Job *>
TimedJobs::getReadyJobs() {
    QList<Job *> readyJobs;

    for (QString guildId : _timedBindings.keys()) {
        for (int i = 0; i < _timedBindings[guildId].length(); ++i) {
            TimedBinding timedBinding = _timedBindings[guildId][i];

            if (QDateTime::currentSecsSinceEpoch() == timedBinding.getStartedAt()) {
                continue;

            } else if (timedBinding.isRunning() && timedBinding.getRemaining() <= 0) {
                EventContext context = timedBinding.getEventContext();

                context.setGuildId(guildId);

                Job *timedJob = new Job;

                timedJob->setContext(timedBinding.getEventContext());

                timedJob->setFunctionMapping(timedBinding.getFunctionMapping());

                readyJobs << timedJob;

                if (timedBinding.isSingleShot()) {
                    _timedBindings[guildId].removeAt(i);

                } else {
                    _timedBindings[guildId][i].start();
                }
            }
        }

        if (_timedBindings[guildId].isEmpty()) {
            _timedBindings.remove(guildId);
        }
    }

    return readyJobs;
}

QList<TimedBinding>
TimedJobs::getAllJobs(const QString &guildId) {
    return _timedBindings[guildId];
}

void
TimedJobs::registerTimedBindings(QSharedPointer<GuildEntity> guild) {
    qint64 currentEpochTime = QDateTime::currentSecsSinceEpoch();

    for (TimedBinding timedBinding : guild->getTimedBindings()) {
        timedBinding.setStartedAt(currentEpochTime);

        _timedBindings[guild->getId()] << timedBinding;
    }

    guild->getTimedBindings().clear();
}

void
TimedJobs::registerTimedBinding(const QString &guildId, TimedBinding &timedBinding) {
    qint64 currentEpochTime = QDateTime::currentSecsSinceEpoch();

    timedBinding.setStartedAt(currentEpochTime);

    _timedBindings[guildId] << timedBinding;
}

void
TimedJobs::clear(const QString &guildId) {
    if (guildId == GuildEntity::DEFAULT_GUILD_ID) {
        _timedBindings.clear();
    } else {
        _timedBindings[guildId].clear();
    }
}

bool
TimedJobs::validateJobIndex(const QString &guildId, const int index) {
    if (_timedBindings[guildId].isEmpty()) {
        return false;
    }

    if (index >= 0 && index <= _timedBindings[guildId].size()) {
        return true;
    }

    _logger->debug(QString("Index (%1) is out of bounds for timed bindings for GuildId: %2")
                   .arg(index)
                   .arg(guildId));

    return false;
}

void
TimedJobs::removeJobById(const QString &guildId, const QString &jobId) {
    for (int i = 0; i < _timedBindings[guildId].size(); ++i) {
        if (_timedBindings[guildId][i].id() == jobId) {
            _timedBindings[guildId].removeAt(i);
        }
    }
}

void
TimedJobs::removeJob(const QString &guildId, const int index) {
    if (!validateJobIndex(guildId, index)) {
        return;
    }

    _timedBindings[guildId].removeAt(index);
}

void
TimedJobs::startJob(const QString &guildId, const int index) {
    if (!validateJobIndex(guildId, index)) {
        return;
    }

    _timedBindings[guildId][index].start();
}

void
TimedJobs::restartJob(const QString &guildId, const int index) {
    if (!validateJobIndex(guildId, index)) {
        return;
    }

    _timedBindings[guildId][index].restart();
}

void
TimedJobs::stopJob(const QString &guildId, const int index) {
    if (!validateJobIndex(guildId, index)) {
        return;
    }

    _timedBindings[guildId][index].stop();
}
