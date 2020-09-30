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

            } else if (timedBinding.isRunning() && timedBinding.getReimaining() <= 0) {
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

        _timedBindings[guild->id()] << timedBinding;
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
TimedJobs::clear() {
    _timedBindings.clear();
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
TimedJobs::resumeJob(const QString &guildId, const int index) {
    if (!validateJobIndex(guildId, index)) {
        return;
    }

    _timedBindings[guildId][index].resume();
}

void
TimedJobs::startJob(const QString &guildId, const int index) {
    if (!validateJobIndex(guildId, index)) {
        return;
    }

    _timedBindings[guildId][index].start();
}

void
TimedJobs::stopJob(const QString &guildId, const int index) {
    if (!validateJobIndex(guildId, index)) {
        return;
    }

    _timedBindings[guildId][index].stop();
}
