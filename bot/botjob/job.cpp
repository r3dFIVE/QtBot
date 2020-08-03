#include "botjob/job.h"


IBotJob::CommandMapping
Job::commandMapping() const {
    return _commandMapping;
}

QString
Job::guildId() {
    return _guildId;
}


void
Job::setCommandMapping(const IBotJob::CommandMapping &commandMapping) {
    _commandMapping = commandMapping;
}

EventContext
Job::context() const {
    return _context;
}

void
Job::setContext(const EventContext &context) {
    _context = context;
}

void
Job::setGuildId(const QString &guildId) {
    _guildId = guildId;
}

void
Job::run() {
    _commandMapping.second->execute(_commandMapping.first.toUtf8(), _context);
}

bool
Job::invokable() const {
    return !_commandMapping.second->running();
}