#ifndef IBINDING_H
#define IBINDING_H

#include "botscript.h"
#include "ibotjob.h"
#include "logging/logfactory.h"
#include "util/globals.h"


class IBinding : public QObject
{

public:    

    static const QString BINDING_TYPE;
    static const QString BINDING_TYPE_COMMAND;
    static const QString BINDING_TYPE_GATEWAY;
    static const QString BINDING_TYPE_TIMED;
    static const QString FUNCTION;
    static const QString REPEAT_AFTER;
    static const QString DESCRIPTION;

    bool validateFunctionMapping(const QMetaObject &metaObject) const;
    IBotJob::FunctionMapping getFunctionMapping() const;
    QString getDescription() const;
    void setDescription(const QString &description);
    void setFunctionMapping(const IBotJob::FunctionMapping &functionMapping);

    virtual bool isValid(const QMetaObject &metaObject) const = 0;

protected:

    IBotJob::FunctionMapping _functionMapping;
    Logger *_logger = LogFactory::getLogger();
    QString _description;
};


#endif // IBINDING_H
