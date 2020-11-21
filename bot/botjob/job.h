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

#ifndef JOB_H
#define JOB_H

#include <QRunnable>

#include "ibotjob.h"

class Job : public QRunnable
{

    EventContext _context;
    IBotJob::FunctionMapping _commandMapping;

public:    
    bool invokable() const;
    EventContext context() const;
    IBotJob::FunctionMapping getFunctionMapping() const;
    QString guildId() const;
    void run() override;
    void setFunctionMapping(const IBotJob::FunctionMapping &functionMapping);
    void setContext(const EventContext &context);
};

#endif // JOB_H
