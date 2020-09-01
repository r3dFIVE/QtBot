#ifndef TIMEDBINDING_H
#define TIMEDBINDING_H

#include "ibinding.h"


class TimedBinding : public IBinding
{
    bool _singleShot = false;
    qint64 _registeredAt = 0;
    qint64 _repeatAfter = 0;
    QJsonValue _sourcePayload;
    QString _scriptName;

public:
    static const QString REPEAT_AFTER;
    static const QString SINGLE_SHOT;
    static const QString SINGLETON;
    static const QString SOURCE_PAYLOAD;

    TimedBinding() {};
    TimedBinding(const TimedBinding &other);

    TimedBinding &operator=(const TimedBinding &other);

    bool isValid(const QMetaObject &metaObject) const override;
    bool isSingleShot() const;
    qint64 getRepeatAfter() const;
    QJsonValue getSourcePayload() const;
    QString getScriptName() const;
    qint64 getRegsteredAt() const;
    void setRegisteredAt(const qint64 registeredAt);
    void setRepeatAfter(const int repeatAfter);
    void setScriptName(const QString &scriptName);
    void setSingleShot(bool singleShot);
    void setSourcePayload(const QJsonValue &sourcePayload);
};


#endif // TIMEDBINDING_H
