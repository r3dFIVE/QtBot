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

    Job* getJobFromQueue(int index);

public:
    friend JobQueue& operator<<(JobQueue &jobQueue, Job* job);
    friend JobQueue& operator<<(JobQueue &jobQueue, QList<Job*> job);

    bool hasJobs() const;
    Job* get();
    void clear(const QString &guildId);
    void pop();
    void queue(Job *job);
};

#endif // JOBQUEUE_H
