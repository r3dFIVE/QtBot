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

#ifndef CORECOMMAND_H
#define CORECOMMAND_H

#include <functional>

#include "botjob/ibotjob.h"
#include "logging/logfactory.h"
#include "payloads/message.h"

class CoreCommand : public IBotJob {
    Q_OBJECT

    std::function<void(const EventContext &context)> _command;

    QString _commandName;

public:
    CoreCommand() {}
    CoreCommand(std::function<void(const EventContext &context)> command) { _command = command; }
    CoreCommand(const CoreCommand &other) { Q_UNUSED(other) }
    ~CoreCommand() {}

    void execute(const QByteArray &command, const EventContext &context) override;
};


#endif // CORECOMMAND_H
