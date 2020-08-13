#ifndef JOB_H
#define JOB_H

#include <QRunnable>

#include "ibotjob.h"

class Job : public QRunnable
{

    EventContext _context;
    IBotJob::FunctionMapping _commandMapping;

public:    
    bool invokable() const;
    EventContext context() const;
    IBotJob::FunctionMapping getFunctionMapping() const;
    QString guildId() const;
    void run() override;
    void setFunctionMapping(const IBotJob::FunctionMapping &functionMapping);
    void setContext(const EventContext &context);
};

#endif // JOB_H
