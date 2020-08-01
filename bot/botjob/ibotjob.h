#ifndef IBOTJOB_H
#define IBOTJOB_H

#include "qml/eventcontext.h"

#include <QByteArray>
#include <QMutex>



class IBotJob {
public:
    typedef QPair<QString, QSharedPointer<IBotJob> > CommandMapping;

    virtual void execute(const QByteArray &command, const EventContext &context) = 0;
    virtual bool running() = 0;
};

#endif // IBOTJOB_H
