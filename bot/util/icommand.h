#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "qml/eventcontext.h"

#include <QByteArray>


class ICommand {

public:
    typedef QPair<QString, QSharedPointer<ICommand>> CommandMapping;

    virtual void execute(const QByteArray &command, QSharedPointer<EventContext> context) = 0;
};

#endif // ICOMMAND_H
