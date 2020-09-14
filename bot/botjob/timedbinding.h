#ifndef TIMEDBINDING_H
#define TIMEDBINDING_H

#include "ibinding.h"


class TimedBinding : public IBinding
{
    Q_OBJECT

    bool _running = true;
    bool _singleShot = false;
    EventContext _eventContext;
    qint64 _remainder = 0;
    qint64 _repeatAfter = 0;
    qint64 _startedAt = 0;
    qint64 _stoppedAt = 0;
    QString _scriptName;

public:
    static const QString EVENT_CONTEXT;
    static const QString REPEAT_AFTER;
    static const QString SINGLE_SHOT;
    static const QString SINGLETON;

    TimedBinding();
    TimedBinding(const TimedBinding &other);
    ~TimedBinding() {}

    TimedBinding &operator=(const TimedBinding &other);

    bool isValid(const QMetaObject &metaObject) const override;
    bool isSingleShot() const;
    bool isRunning() const;
    qint64 getRepeatAfter() const;
    EventContext getEventContext() const;
    qint64 getReimaining();
    QString getScriptName() const;
    qint64 getStartedAt() const;
    void resume();
    void setStartedAt(const qint64 startedAt);
    void setRepeatAfter(const int repeatAfter);
    void setScriptName(const QString &scriptName);
    void setSingleShot(bool singleShot);
    void setEventContext(const EventContext &sourcePayload);
    void start();
    void stop();
};

Q_DECLARE_METATYPE(TimedBinding)

#endif // TIMEDBINDING_H
