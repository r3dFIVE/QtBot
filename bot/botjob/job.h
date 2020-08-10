#ifndef JOB_H
#define JOB_H

#include <QRunnable>

#include "ibotjob.h"

class Job : public QRunnable
{

    EventContext _context;
    IBotJob::CommandMapping _commandMapping;

public:    
    bool invokable() const;
    EventContext context() const;
    IBotJob::CommandMapping commandMapping() const;
    QString guildId() const;
    void run() override;
    void setCommandMapping(const IBotJob::CommandMapping &commandMapping);
    void setContext(const EventContext &context);
};

#endif // JOB_H
