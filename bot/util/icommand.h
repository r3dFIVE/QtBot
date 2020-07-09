#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QByteArray>

#include <payloads/message.h>



class ICommand {

public:
    typedef QPair<QString, QSharedPointer<ICommand>> CommandMapping;

    virtual void execute(const QByteArray &command, const Message &message) = 0;
};

#endif // ICOMMAND_H
