#include "botjob/job.h"


IBotJob::FunctionMapping
Job::getFunctionMapping() const {
    return _commandMapping;
}

QString
Job::guildId() const {
    return _commandMapping.second->getGuildId();
}


void
Job::setFunctionMapping(const IBotJob::FunctionMapping &functionMapping) {
    _commandMapping = functionMapping;
}

EventContext
Job::context() const {
    return _context;
}

void
Job::setContext(const EventContext &context) {
    _context = context;

    _context.splitArgs();
}

void
Job::run() {
    _commandMapping.second->execute(_commandMapping.first.toUtf8(), _context);
}

bool
Job::invokable() const {
    return _commandMapping.second->invokable();
}
