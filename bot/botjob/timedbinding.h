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

#ifndef TIMEDBINDING_H
#define TIMEDBINDING_H

#include "ibinding.h"


class TimedBinding : public IBinding
{
    Q_OBJECT

    bool _enabled = true;
    bool _running = true;
    bool _singleShot = true;
    bool _singleton = false;
    bool _forceEnable = false;
    EventContext _eventContext;    
    qint64 _remainder = 0;
    int _fireAfter = 0;
    qint64 _startedAt = 0;    
    qint64 _stoppedAt = 0;    
    QString _scriptName;
    QString _id;

    Q_PROPERTY(bool single_shot READ isSingleShot WRITE setSingleShot)
    Q_PROPERTY(EventContext context READ getEventContext WRITE setEventContext)
    Q_PROPERTY(qint64 fire_after READ getFireAfter WRITE setFireAfter)

    void copy(const TimedBinding &other);
public:
    static const QString CONTEXT;
    static const QString FIRE_AFTER;
    static const QString SINGLE_SHOT;
    static const QString SINGLETON;
    static const QString FORCE_ENABLE;

    TimedBinding();
    TimedBinding(const TimedBinding &other);
    ~TimedBinding() {}

    TimedBinding &operator=(const TimedBinding &other);


    bool isValid(const QMetaObject &metaObject) const override;
    bool isSingleShot() const;
    bool isSingleton() const;
    bool isRunning() const;
    bool isEnabled() const;
    bool forceEnable() const;
    qint64 getFireAfter() const;
    EventContext getEventContext() const;
    qint64 getRemaining();
    QString getScriptName() const;
    qint64 getStartedAt() const;
    QString id() const;
    void restart();
    void setEnabled(const bool enabled);
    void setStartedAt(const qint64 startedAt);
    void setFireAfter(const int fireAfter);
    void setScriptName(const QString &scriptName);
    void setSingleShot(bool singleShot);
    void setSingleton(bool singleton);
    void setForceEnable(bool forceEnable);
    void setEventContext(const EventContext &sourcePayload);
    void setId(const QString &id);
    void start();
    void stop();
};

Q_DECLARE_METATYPE(TimedBinding)

#endif // TIMEDBINDING_H
