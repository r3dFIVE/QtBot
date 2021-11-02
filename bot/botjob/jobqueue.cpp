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

#include "jobqueue.h"

#include "gateway.h"


JobQueue&
operator<<(JobQueue &jobQueue, Job *job) {
    jobQueue.queue(job);

    return jobQueue;
}

JobQueue&
operator<<(JobQueue &jobQueue, QList<Job *> jobs) {
    for (auto job : jobs) {
        jobQueue.queue(job);
    }

    return jobQueue;
}


Job*
JobQueue::get() {
    if (readyJob) {
        return readyJob;
    }

    if (_jobQueue.size() == 0) {
        return nullptr;
    }

    for(int i = _lastJobGuildIndex; i < _jobQueue.size(); ++i) {
        Job *availableJob = getJobFromQueue(i);

        if (availableJob) {
            readyJob = availableJob;

            return readyJob;
        }
    }

    for(int i = 0; i < _lastJobGuildIndex; ++i) {
        Job *availableJob = getJobFromQueue(i);

        if (availableJob) {
            readyJob = availableJob;

            return readyJob;
        }
    }

    return nullptr;
}

Job*
JobQueue::getJobFromQueue(int index) {        
    QString guildId = _jobQueue.keys().at(index);

    for (int i = 0; i < _jobQueue[guildId].length(); ++i) {
        Job *job = _jobQueue[guildId].at(i);

        if (job->invokable()) {
            readyJob = job;

            _jobQueue[guildId].removeAt(i);

            if (_jobQueue[guildId].size() == 0) {
                _jobQueue.remove(guildId);
            }

            _lastJobGuildIndex = index;

            if (_jobQueue.size() > 0 && _lastJobGuildIndex == _jobQueue.size()) {
                _lastJobGuildIndex = 0;
            }

            return readyJob;
        }
    }

    return nullptr;
}

void
JobQueue::pop() {
    readyJob = nullptr;
}

void
JobQueue::queue(Job *job) {
    _jobQueue[job->guildId()] << job;
}

bool
JobQueue::hasJobs() const {
    return !_jobQueue.isEmpty();
}

void
JobQueue::clear(const QString &guildId) {
    if (guildId == GuildEntity::DEFAULT_GUILD_ID) {
        _jobQueue.clear();
    } else {
        _jobQueue[guildId].clear();
    }
}
