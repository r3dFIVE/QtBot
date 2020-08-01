#ifndef BOTJOB_H
#define BOTJOB_H

#include <QRunnable>

#include "ibotjob.h"



class BotJob : public QRunnable
{
    IBotJob::CommandMapping _commandMapping;
    EventContext _context;

    bool _invokable;

public:
    BotJob();

    void run() override;
    IBotJob::CommandMapping commandMapping() const;
    void setCommandMapping(const IBotJob::CommandMapping &commandMapping);
    EventContext context() const;
    void setContext(const EventContext &context);
    bool invokable() const;
    void setInvokable(bool invokable);
};

#endif // BOTJOB_H
