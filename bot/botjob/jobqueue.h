#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <QMap>
#include <QList>

#include "job.h"


class JobQueue
{
    int _lastJobGuildIndex = 0;

    Job *readyJob = nullptr;
    QMap<QString, QList<Job*>> _jobQueue;

    Job* getJobFromGuildQueue(int index);

public:
    friend JobQueue& operator<<(JobQueue &jobQueue, Job* job);

    bool hasJobs() const;
    Job* get();
    void pop();
    void queue(Job *job);
};

#endif // JOBQUEUE_H
