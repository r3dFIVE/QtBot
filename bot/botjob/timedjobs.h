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
    QList<TimedBinding> getAllJobs(const QString &guildId);
    void clear();
    void registerTimedBindings(QSharedPointer<GuildEntity> guild);
    void registerTimedBinding(const QString &guildId, TimedBinding &timedBinding);
};

#endif // TIMEDJOBS_H
