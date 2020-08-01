#include "botjob/botjob.h"



BotJob::BotJob() : _invokable(false) { }


IBotJob::CommandMapping
BotJob::commandMapping() const {
    return _commandMapping;
}

void
BotJob::setCommandMapping(const IBotJob::CommandMapping &commandMapping) {
    _commandMapping = commandMapping;
}

EventContext
BotJob::context() const {
    return _context;
}

void
BotJob::setContext(const EventContext &context) {
    _context = context;
}

void
BotJob::run() {
    _commandMapping.second->execute(_commandMapping.first.toUtf8(), _context);
}

bool
BotJob::invokable() const {
    return _invokable;
}

void
BotJob::setInvokable(bool invokable) {
    _invokable = invokable;
}
