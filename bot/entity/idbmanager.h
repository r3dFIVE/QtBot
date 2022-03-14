#ifndef IDBMANAGER_H
#define IDBMANAGER_H

#include <QSharedPointer>

#include "guildentity.h"
#include "botjob/databasecontext.h"
#include "logging/logfactory.h"
#include "payloads/gatewaypayload.h"


class IDBManager : public QObject {
    Q_OBJECT

    Logger *_logger;

protected:

    IDBManager(QObject *parent = nullptr);

    static const QString COMMAND_RESTRICTIONS;

    DatabaseContext _databaseContext;

    void notImplemented(QString name);

public:
    virtual void initGuild(QSharedPointer<GuildEntity> payload) = 0;
    virtual void init() = 0;
    virtual void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) = 0;
    virtual void saveEvent(QSharedPointer<GatewayPayload> payload) = 0;
};

#endif // IDBMANAGER_H
