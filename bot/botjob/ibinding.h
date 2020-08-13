#ifndef IBINDING_H
#define IBINDING_H

#include <QJsonObject>

#include "botscript.h"
#include "ibotjob.h"
#include "logging/logfactory.h"
#include "util/globals.h"


class IBinding : public QObject
{


public:    
    static const QString BINDING_TYPE;
    static const QString FUNCTION;
    static const QString GATEWAY_EVENT;
    static const QString REPEAT_AFTER;


    IBinding() {}
    IBinding(const QString &commandName,
             const IBotJob::FunctionMapping &functionMapping,
             const QString &scriptName);

    IBotJob::FunctionMapping getFunctionMapping() const;
    QString getDescription() const;
    QString getScriptName() const;
    void setScriptName(const QString &scriptName);
    void setBindingType(const QString &bindingType);
    void setDescription(const QString &description);
    void setFunctionMapping(const IBotJob::FunctionMapping &functionMapping);

    virtual bool isValid(const QMetaObject &metaObject) const = 0;

    void setGatewayEvent(const GatewayEvents::Events &gatewayEvent);
    void setRepeatAfter(int seconds);

protected:

    IBotJob::FunctionMapping _functionMapping;
    Logger *_logger;
    QString _description;
    QString _scriptName;

    QByteArray buildFunctionSearchString() const;
};


#endif // IBINDING_H
