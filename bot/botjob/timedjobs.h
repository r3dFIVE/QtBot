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

#ifndef TIMEDJOBS_H
#define TIMEDJOBS_H

#include "timedbinding.h"
#include "entity/guildentity.h"


class TimedJobs
{
    Logger *_logger = LogFactory::getLogger();
    qint64 _counter = 0;
    QMap<QString, QList<TimedBinding> > _timedBindings;

    bool validateJobIndex(const QString &guildId, const int index);

public:
    bool hasJobs() const;
    QList<Job *> getReadyJobs();
    QList<TimedBinding> getAllJobs(const QString &guildId);
    void clear();
    void registerTimedBindings(QSharedPointer<GuildEntity> guild);
    void registerTimedBinding(const QString &guildId, TimedBinding &timedBinding);
    void removeJob(const QString &guildId, const int index);
    void removeJobById(const QString &guildId, const QString &jobId);
    void resumeJob(const QString &guildId, const int index);
    void startJob(const QString &guildId, const int index);
    void stopJob(const QString &guildId, const int index);
};

#endif // TIMEDJOBS_H
