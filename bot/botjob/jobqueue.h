#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <QMap>
#include <QList>

#include "ibotjob.h"


class JobQueue
{
    QMap<QString, QList<QSharedPointer<IBotJob>> > _jobQueue;


public:
    JobQueue();
};

#endif // JOBQUEUE_H
