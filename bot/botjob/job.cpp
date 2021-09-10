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
