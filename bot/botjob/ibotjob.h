#ifndef IBOTJOB_H
#define IBOTJOB_H

#include <QByteArray>
#include <QMutex>

#include "payloads/eventcontext.h"

class IBotJob : public QObject
{
    Q_OBJECT

protected:
    QString _guildId;

public:
    typedef QPair<QString, QSharedPointer<IBotJob> > FunctionMapping;

    virtual bool invokable() = 0;
    virtual void execute(const QByteArray &command, const EventContext &context) = 0;

    QString getGuildId() { return _guildId; }
    void setGuildId(const QString &guildId) { _guildId = guildId; }
};

#endif // IBOTJOB_H
