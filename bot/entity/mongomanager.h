#ifndef MONGOMANAGER_H
#define MONGOMANAGER_H

#include <QObject>

#include "imanager.h"
#include "mongodb.h"


class MongoManager : public IManager
{

    QSet<QString> _availableCollections;
    QSharedPointer<MongoDB> _mongoDB;

public:

    MongoManager(DatabaseContext context) {
        _databaseContext = context;
    }

    void initGuild(QSharedPointer<GuildEntity> guildEntity) override;
    void init() override;
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) override;
    void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) override;
    void saveEvent(QSharedPointer<GatewayPayload> payload) override;
};

#endif // MONGOMANAGER_H
