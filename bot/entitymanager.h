#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>

#include "entity/guildentity.h"
#include "payloads/guild.h"
#include "payloads/gatewaypayload.h"


class EntityManager : public QObject
{
    Q_OBJECT

    static const QString CONNECTION_NAME;
    static const QString COMMAND_RESTRICTIONS;
    static const QString SQL_CREATE_COMMAND_RESTRICTIONS_TABLE_SQLITE;
    static const QString SQL_CREATE_COMMAND_RESTRICTIONS_TABLE;
    static const QString SQL_SELECT_COMMAND_RESTRICTION_ID;
    static const QString SQL_INSERT_COMMAND_RESTRICTION;
    static const QString SQL_UPDATE_COMMAND_RESTRICTION;
    static const QString SQL_REMOVE_COMMAND_RESTRICTION;
    static const QString SQL_REMOVE_COMMAND_RESTRICTION_FOR_ID;
    static const QString SQL_SELECT_COMMAND_RESTRICTIONS_FOR_GUILD;

    QSqlDatabase _database;
    DatabaseContext _databaseContext;
    Logger *_logger = LogFactory::getLogger();

    bool isDbOpen();
    void insertRestriction(const QString &guildId,
                           const QString &commandName,
                           const QString &targetId,
                           CommandRestrictions::RestrictionState state);
    void updateRestriction(const QString &guildId,
                           const QString &commandName,
                           const QString &targetId,
                           CommandRestrictions::RestrictionState state);
    void clearCommand(QSharedPointer<CommandRestrictions> restrictions);
    void clearCommandForId(QSharedPointer<CommandRestrictions> restrictions);

public:
    EntityManager(QSharedPointer<Settings> settings) : _databaseContext(settings) {}


signals:
    void guildInitialized(QSharedPointer<GuildEntity> guildEntity);

public slots:
    void initGuild(QSharedPointer<GuildEntity> payload);
    void initGuildFromPayload(QSharedPointer<GatewayPayload> payload);
    void init();
    void restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions);
    void restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions);
};

#endif // ENTITYMANAGER_H
