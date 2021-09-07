#ifndef IDBMANAGER_H
#define IDBMANAGER_H

#include <QSharedPointer>

#include "guildentity.h"
#include "botjob/databasecontext.h"
#include "logging/logfactory.h"
#include "payloads/gatewaypayload.h"


class IDBManager : public QObject {
    Logger *_logger = LogFactory::getLogger();

    void notImplemented(QString name);

protected:

    static const QString COMMAND_RESTRICTIONS;

    DatabaseContext _databaseContext;

public:

    virtual void initGuild(QSharedPointer<GuildEntity> payload) = 0;
    virtual void init() = 0;
    virtual void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) = 0;
    virtual void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) = 0;
    virtual void saveEvent(QSharedPointer<GatewayPayload> payload);
};

#endif // IDBMANAGER_H
