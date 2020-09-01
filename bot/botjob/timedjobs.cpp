#include "timedjobs.h"


bool
TimedJobs::hasJobs() const {
    return !_timedBindings.isEmpty();
}

QList<Job *>
TimedJobs::getReadyJobs() {
    QList<Job *> readyJobs;

    if (_counter == 0) {
        _counter = QDateTime::currentSecsSinceEpoch();
    }

    _counter++;

    for (QString guildId : _timedBindings.keys()) {
        for (int i = 0; i < _timedBindings[guildId].length(); ++i) {
            TimedBinding binding = _timedBindings[guildId].at(i);

            qint64 c = (_counter - binding.getRegsteredAt()) % binding.getRepeatAfter();

            if (c == 0) {
                EventContext context;

                context.setSourcePayload(binding.getSourcePayload().toObject());

                context.setGuildId(guildId);

                Job *timedJob = new Job;

                timedJob->setContext(context);

                timedJob->setFunctionMapping(binding.getFunctionMapping());

                readyJobs << timedJob;

                if (binding.isSingleShot()) {
                    _timedBindings[guildId].removeAt(i);
                }
            }
        }

        if (_timedBindings[guildId].isEmpty()) {
            _timedBindings.remove(guildId);
        }
    }

    return readyJobs;
}

void
TimedJobs::registerTimedBindings(QSharedPointer<GuildEntity> guild) {
    qint64 currentEpochTime = QDateTime::currentSecsSinceEpoch();

    for (TimedBinding binding : guild->getTimedBindings()) {
        binding.setRegisteredAt(currentEpochTime);

        _timedBindings[guild->id()] << binding;
    }

    guild->getTimedBindings().clear();
}
