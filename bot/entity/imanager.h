#ifndef IMANAGER_H
#define IMANAGER_H

#include <QSharedPointer>

#include "guildentity.h"
#include "payloads/gatewaypayload.h"

class IManager : public QObject {

    Logger *_logger = LogFactory::getLogger();

    void notImplemented(QString name) {
        _logger->trace(QString("%1 is not currently implement for given database type.").arg(name));
    }

public:
    virtual void initGuild(QSharedPointer<GuildEntity> payload) = 0;
    virtual void init() = 0;
    virtual void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) = 0;
    virtual void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) = 0;
    virtual void saveEvent(QSharedPointer<GatewayPayload> payload) {
        notImplemented("saveEvent");
    }
};

#endif // IMANAGER_H
