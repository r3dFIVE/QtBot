#include "jobqueue.h"

JobQueue&
operator<<(JobQueue &jobQueue, Job *job) {
    jobQueue.queue(job);

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

    for(int i = _lastJobGuildIndex; i < _jobQueue.keys().length(); ++i) {
        Job *availableJob = getJobFromGuildQueue(i);

        if (availableJob) {
            readyJob = availableJob;

            return readyJob;
        }
    }

    for(int i = 0; i < _lastJobGuildIndex; ++i) {
        Job *availableJob = getJobFromGuildQueue(i);

        if (availableJob) {
            readyJob = availableJob;

            return readyJob;
        }
    }

    return nullptr;
}

Job*
JobQueue::getJobFromGuildQueue(int index) {
    QString guildId =  _jobQueue.keys().at(index);

    for (int i = 0; i < _jobQueue[guildId].length(); ++i) {
        Job *job = _jobQueue[guildId].at(i);

        if (job->invokable()) {
            readyJob = job;

            _jobQueue[guildId].removeAt(i);

            if (_jobQueue[guildId].size() == 0) {
                _jobQueue.remove(guildId);
            }

            _lastJobGuildIndex = index;

            if (_jobQueue.keys().size() > 0 && _lastJobGuildIndex == _jobQueue.keys().size()) {
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
