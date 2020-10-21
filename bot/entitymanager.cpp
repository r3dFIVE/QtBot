#include "entitymanager.h"

#include <QSqlError>

#include "util/enumutils.h"


const QString EntityManager::CONNECTION_NAME = "entityManager";
const QString EntityManager::COMMAND_RESTRICTIONS = "CommandRestrictions";
const QString EntityManager::SQL_CREATE_COMMAND_RESTRICTIONS_TABLE = QString("CREATE TABLE %1 (id integer PRIMARY KEY AUTO_INCREMENT, guild_id varchar(256), command_name varchar(256), target_id varchar(256), state integer);").arg(COMMAND_RESTRICTIONS);
const QString EntityManager::SQL_SELECT_COMMAND_RESTRICTION_ID = QString("SELECT id FROM %1 WHERE guild_id = ? AND target_id = ? AND command_name = ?;").arg(COMMAND_RESTRICTIONS);
const QString EntityManager::SQL_INSERT_COMMAND_RESTRICTION = QString("INSERT INTO %1 (guild_id, command_name, target_id, state) VALUES (?, ?, ?, ?);").arg(COMMAND_RESTRICTIONS);
const QString EntityManager::SQL_UPDATE_COMMAND_RESTRICTION = QString("UPDATE %1 SET state = ? WHERE guild_id = ? and command_name = ? AND target_id = ?;").arg(COMMAND_RESTRICTIONS);
const QString EntityManager::SQL_REMOVE_COMMAND_RESTRICTION = QString("DELETE FROM %1 WHERE guild_id = ? AND command_name = ?;").arg(COMMAND_RESTRICTIONS);
const QString EntityManager::SQL_REMOVE_COMMAND_RESTRICTION_FOR_ID = QString("DELETE FROM %1 WHERE guild_id = ? AND command_name = ? AND target_id = ?;").arg(COMMAND_RESTRICTIONS);
const QString EntityManager::SQL_SELECT_COMMAND_RESTRICTIONS_FOR_GUILD = QString("SELECT command_name, target_id, state FROM %1 WHERE guild_id = ?;").arg(COMMAND_RESTRICTIONS);

void
EntityManager::initGuildFromPayload(QSharedPointer<GatewayPayload> payload) {
    Guild jsonGuild(payload->getD());

    QSharedPointer<GuildEntity> guildEntity = QSharedPointer<GuildEntity>(new GuildEntity(jsonGuild));

    Guild guild(payload->getD());

    guildEntity->setId(guild.getId().toString());

    QObject::connect(guildEntity.data(), &GuildEntity::restrictionsRemoval, this, &EntityManager::restrictionsRemoval);

    QObject::connect(guildEntity.data(), &GuildEntity::restrictionsUpdate, this, &EntityManager::restrictionsUpdate);

    initGuild(guildEntity);
}

void
EntityManager::init() {
    _database = QSqlDatabase::addDatabase(_databaseContext.driverName, CONNECTION_NAME);

    _database.setDatabaseName(_databaseContext.databaseName);

    int type = EnumUtils::keyToValue<SettingsParam::Database::DatabaseType>(_databaseContext.driverName);

    if (type != SettingsParam::Database::QSQLITE) {
        _database.setHostName(_databaseContext.hostName);

        _database.setUserName(_databaseContext.userName);

        _database.setPassword(_databaseContext.password);

        _database.setPort(_databaseContext.port);
    }

    if (isDbOpen()) {
        _logger->info("EntityManager successfully connected to database...");

        if (!_database.tables().contains(COMMAND_RESTRICTIONS)) {
            _database.exec(SQL_CREATE_COMMAND_RESTRICTIONS_TABLE);
        }
    }
}

bool
EntityManager::isDbOpen() {
    if (!_database.open()) {
        _logger->warning(QString("EntityManager failed to open database... %1").arg(_database.lastError().text()));

        return false;
    }

    return true;
}

void
EntityManager::restrictionsUpdate(QSharedPointer<CommandRestrictions> restrictions) {
    if (!isDbOpen()) {
        return;
    }

    QSqlQuery query(_database);

    QMap<QString, CommandRestrictions::RestrictionState> restrictionMap = restrictions->getRestrictions();

    for (auto commandName : restrictionMap.keys()) {
        query.prepare(SQL_SELECT_COMMAND_RESTRICTION_ID);

        query.bindValue(0, restrictions->getGuildId());

        query.bindValue(1, restrictions->getTargetId());

        query.bindValue(2, commandName);

        query.exec();       

        if (query.size() > 0) {
            updateRestriction(restrictions->getGuildId(),
                              commandName,
                              restrictions->getTargetId(),
                              restrictionMap[commandName]);
        } else if (query.size() == 0) {
            insertRestriction(restrictions->getGuildId(),
                              commandName,
                              restrictions->getTargetId(),
                              restrictionMap[commandName]);
        } else {
            _logger->warning(query.lastError().text());
        }
    }
}

void
EntityManager::restrictionsRemoval(QSharedPointer<CommandRestrictions> restrictions) {
    if (restrictions->getTargetId().isEmpty()) {
        clearCommand(restrictions);
    } else {
        clearCommandForId(restrictions);
    }
}

void
EntityManager::clearCommand(QSharedPointer<CommandRestrictions> restrictions) {
    QSqlQuery query(_database);

    QMap<QString, CommandRestrictions::RestrictionState> restrictionMap = restrictions->getRestrictions();

    for (auto commandName : restrictionMap.keys()) {
        query.prepare(SQL_REMOVE_COMMAND_RESTRICTION);

        query.bindValue(0, restrictions->getGuildId());

        query.bindValue(1, commandName);

        query.exec();

        if (query.lastError().isValid()) {
            _logger->warning(query.lastError().text());
        }
    }
}

void
EntityManager::clearCommandForId(QSharedPointer<CommandRestrictions> restrictions) {
    QSqlQuery query(_database);

    QMap<QString, CommandRestrictions::RestrictionState> restrictionMap = restrictions->getRestrictions();

    for (auto commandName : restrictionMap.keys()) {
        query.prepare(SQL_REMOVE_COMMAND_RESTRICTION_FOR_ID);

        query.bindValue(0, restrictions->getGuildId());

        query.bindValue(1, commandName);

        query.bindValue(2, restrictions->getTargetId());

        query.exec();

        if (query.lastError().isValid()) {
            _logger->warning(query.lastError().text());
        }
    }
}

void
EntityManager::insertRestriction(const QString &guildId,
                                 const QString &commandName,
                                 const QString &targetId,
                                 CommandRestrictions::RestrictionState state) {
    QSqlQuery query(_database);

    query.prepare(SQL_INSERT_COMMAND_RESTRICTION);

    query.bindValue(0, guildId);

    query.bindValue(1, commandName);

    query.bindValue(2, targetId);

    query.bindValue(3, state);

    query.exec();

    if (query.lastError().isValid()) {
        _logger->warning(query.lastError().text());
    }
}

void
EntityManager::updateRestriction(const QString &guildId,
                                 const QString &commandName,
                                 const QString &targetId,
                                 CommandRestrictions::RestrictionState state) {
    QSqlQuery query(_database);

    query.prepare(SQL_UPDATE_COMMAND_RESTRICTION);

    query.bindValue(0, state);

    query.bindValue(1, guildId);

    query.bindValue(2, commandName);

    query.bindValue(3, targetId);

    query.exec();

    if (query.lastError().isValid()) {
        _logger->warning(query.lastError().text());
    }
}

void
EntityManager::initGuild(QSharedPointer<GuildEntity> guildEntity) {
    QSqlQuery query(_database);

    query.prepare(SQL_SELECT_COMMAND_RESTRICTIONS_FOR_GUILD);

    query.bindValue(0, guildEntity->id());

    query.exec();

    if (query.lastError().isValid()) {
        _logger->warning(query.lastError().text());

        return;
    }

    QMap<QString, QMap<QString, CommandRestrictions::RestrictionState> > mappedStateIdsByCommand;

    while (query.next()) {
        QString commandName = query.value(0).toString();

        QString targetId = query.value(1).toString();

        int state = query.value(2).toInt();

        mappedStateIdsByCommand[commandName][targetId] = CommandRestrictions::RestrictionState(state);
    }

    guildEntity->setMappedStateIdsByCommand(mappedStateIdsByCommand);

    emit guildInitialized(guildEntity);
}
