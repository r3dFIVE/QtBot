#ifndef IBOTJOB_H
#define IBOTJOB_H

#include <QByteArray>
#include <QMutex>

#include "payloads/eventcontext.h"

class IBotJob {

protected:
    QString _guildId;

public:
    typedef QPair<QString, QSharedPointer<IBotJob> > CommandMapping;

    virtual void execute(const QByteArray &command, const EventContext &context) = 0;
    virtual bool invokable() = 0;

    QString guildId() { return _guildId; }
    void setGuildId(const QString &guildId) { _guildId = guildId; }

};

#endif // IBOTJOB_H
