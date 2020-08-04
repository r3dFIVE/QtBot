#ifndef JOB_H
#define JOB_H

#include <QRunnable>

#include "ibotjob.h"

class Job : public QRunnable
{

    EventContext _context;
    IBotJob::CommandMapping _commandMapping;
    QString _guildId;

public:    
    bool invokable() const;
    EventContext context() const;
    IBotJob::CommandMapping commandMapping() const;
    QString guildId();
    void run() override;
    void setCommandMapping(const IBotJob::CommandMapping &commandMapping);
    void setContext(const EventContext &context);
    void setGuildId(const QString &guildId);
};

#endif // JOB_H
