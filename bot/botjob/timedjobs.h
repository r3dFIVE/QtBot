#ifndef TIMEDJOBS_H
#define TIMEDJOBS_H

#include "timedbinding.h"
#include "entity/guildentity.h"


class TimedJobs
{
    Logger *_logger = LogFactory::getLogger();
    qint64 _counter = 0;
    QMap<QString, QList<TimedBinding> > _timedBindings;

    bool validateJobIndex(const QString &guildId, const int index);

public:
    bool hasJobs() const;
    QList<Job *> getReadyJobs();
    QList<TimedBinding> getAllJobs(const QString &guildId);
    void clear();
    void registerTimedBindings(QSharedPointer<GuildEntity> guild);
    void registerTimedBinding(const QString &guildId, TimedBinding &timedBinding);
    void removeJob(const QString &guildId, const int index);
    void resumeJob(const QString &guildId, const int index);
    void startJob(const QString &guildId, const int index);
    void stopJob(const QString &guildId, const int index);
};

#endif // TIMEDJOBS_H
