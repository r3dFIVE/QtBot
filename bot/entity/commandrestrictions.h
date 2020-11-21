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

#ifndef COMMANDRESTRICTIONS_H
#define COMMANDRESTRICTIONS_H

#include <QObject>
#include <QMap>

class CommandRestrictions : public QObject
{
    Q_OBJECT

public:

    enum RestrictionState {
        DISABLED = 0,
        ENABLED = 1
    };
    Q_ENUM(RestrictionState)

    CommandRestrictions(const QString &guildId,
                        const QString &targetId,
                        const QMap<QString, RestrictionState> &restrictions)
        : _guildId(guildId), _targetId(targetId), _restrictions(restrictions) {}

    inline QString getGuildId() const {
        return _guildId;
    }

    inline QString getTargetId() const {
        return _targetId;
    }

    inline QMap<QString, RestrictionState> getRestrictions() const {
        return _restrictions;
    }

private:
    QString _guildId;
    QString _targetId;
    QMap<QString, RestrictionState> _restrictions;
};

#endif // COMMANDRESTRICTIONS_H
