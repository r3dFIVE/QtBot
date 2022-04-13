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

#ifndef IBOTJOB_H
#define IBOTJOB_H

#include <QByteArray>
#include <QMutex>

#include "payloads/eventcontext.h"
#include "helppage.h"

class IBotJob : public QObject
{
    Q_OBJECT

protected:
    QString _guildId;
    QMutex _runLock;

public:
    typedef QPair<QString, IBotJob*> FunctionMapping;

    bool invokable() {
        return _runLock.tryLock();
    }

    virtual void execute(const QByteArray &command, const EventContext &context) = 0;

    QString getGuildId() { return _guildId; }
    void setGuildId(const QString &guildId) { _guildId = guildId; }
};

#endif // IBOTJOB_H
