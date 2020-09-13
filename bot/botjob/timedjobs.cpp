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
            TimedBinding binding = _timedBindings[guildId].at(i);

            qint64 currentEpochTime = QDateTime::currentSecsSinceEpoch();

            if (currentEpochTime == binding.getStartedAt()) {
                continue;

            } else if ((currentEpochTime - binding.getStartedAt()) - binding.getRepeatAfter() >= 0) {
                EventContext context = binding.getEventContext();

                context.setGuildId(guildId);

                Job *timedJob = new Job;

                timedJob->setContext(binding.getEventContext());

                timedJob->setFunctionMapping(binding.getFunctionMapping());

                readyJobs << timedJob;

                if (binding.isSingleShot()) {
                    _timedBindings[guildId].removeAt(i);

                } else {
                    binding.setStartedAt(currentEpochTime);
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
