#ifndef TIMEDBINDING_H
#define TIMEDBINDING_H

#include "ibinding.h"


class TimedBinding : public IBinding
{
    Q_OBJECT

    bool _running = true;
    bool _singleShot = true;
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

public:
    static const QString CONTEXT;
    static const QString FIRE_AFTER;
    static const QString SINGLE_SHOT;
    static const QString SINGLETON;

    TimedBinding();
    TimedBinding(const TimedBinding &other);
    ~TimedBinding() {}

    TimedBinding &operator=(const TimedBinding &other);


    bool isValid(const QMetaObject &metaObject) const override;
    bool isSingleShot() const;
    bool isRunning() const;
    qint64 getFireAfter() const;
    EventContext getEventContext() const;
    qint64 getReimaining();
    QString getScriptName() const;
    qint64 getStartedAt() const;
    QString id() const;
    void resume();
    void setStartedAt(const qint64 startedAt);
    void setFireAfter(const int fireAfter);
    void setScriptName(const QString &scriptName);
    void setSingleShot(bool singleShot);
    void setEventContext(const EventContext &sourcePayload);
    void setId(const QString &id);
    void start();
    void stop();
};

Q_DECLARE_METATYPE(TimedBinding)

#endif // TIMEDBINDING_H
