#ifndef TIMEDJOBS_H
#define TIMEDJOBS_H

#include "timedbinding.h"
#include "entity/guildentity.h"


class TimedJobs
{
    qint64 _counter = 0;
    QMap<QString, QList<TimedBinding> > _timedBindings;

public:
    bool hasJobs() const;
    QList<Job *> getReadyJobs();
    void registerTimedBindings(QSharedPointer<GuildEntity> guild);
};

#endif // TIMEDJOBS_H
