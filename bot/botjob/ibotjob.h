#ifndef IBOTJOB_H
#define IBOTJOB_H

#include <QByteArray>
#include <QMutex>

#include "qml/eventcontext.h"

class IBotJob {

public:
    typedef QPair<QString, QSharedPointer<IBotJob> > CommandMapping;

    virtual void execute(const QByteArray &command, const EventContext &context) = 0;
    virtual bool running() = 0;
};

#endif // IBOTJOB_H
