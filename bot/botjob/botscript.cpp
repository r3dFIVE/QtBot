#include "botjob/botscript.h"

#include <QSqlError>
#include <QThread>

#include "util/serializationutils.h"
#include "util/enumutils.h"

BotScript::BotScript(const BotScript &other) {
    _database = other._database;

    _query = other._query;
}

BotScript
&BotScript::operator=(const BotScript &other) {
    _database = other._database;

    _query = other._query;

    return *this;
}

DatabaseContext
BotScript::getDatabaseContext() const
{
    return _databaseContext;
}

void
BotScript::setDatabaseContext(const DatabaseContext &databaseContext) {
    _databaseContext = databaseContext;

    setConnectionName();
}

QVariant
BotScript::buildResponseVariant(QSharedPointer<EventContext> apiResponse) {
    QVariant repsonseContext;

    if (apiResponse) {
        repsonseContext = SerializationUtils::toVariant(*apiResponse);
    }

    return repsonseContext;
}

void
BotScript::setEventBindingsJson(const QJsonArray &eventBindingsJson) {
    _eventBindingsJson = eventBindingsJson;
}

QJsonArray
BotScript::getEventBindingsJson() const {
    return _eventBindingsJson;
}

bool
BotScript::invokable() {
    bool canLock = _runLock.tryLock();

    if (canLock) {
        _runLock.unlock();
    }

    return canLock;
}

QString
BotScript::findFunctionMapping(const QString &command) const {
    return _commands[command].toString();
}

void
BotScript::setScriptName(const QString &scriptName) {
    _scriptName = scriptName;
}

void
BotScript::setScriptCommands(const QMap<QString, QVariant> &commands) {
    _commands = commands;
}

void
BotScript::execute(const QByteArray &command, const EventContext &context) {
    QMutexLocker lock(&_runLock);

    QVariant returnValue;

    QMetaObject::invokeMethod(this, command,
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, returnValue),
                              Q_ARG(QVariant, SerializationUtils::toVariant(context)));
}

void
BotScript::pause(int ms) {
    QThread::msleep(ms);
}

bool
BotScript::dbOpen() {
    closeExistingConnection();

    _database = QSqlDatabase::addDatabase(_databaseContext.driverName, _databaseContext.getConnectionName());

    _database.setHostName(_databaseContext.hostName);

    _database.setUserName(_databaseContext.userName);

    _database.setPassword(_databaseContext.password);

    _database.setDatabaseName(_databaseContext.databaseName);

    _query = QSqlQuery(_database);

    return _database.open();
}

void
BotScript::closeExistingConnection() {
    if (QSqlDatabase::contains(_databaseContext.getConnectionName())) {
        _query.clear();

        _database.close();

        _database = QSqlDatabase();

        QSqlDatabase::removeDatabase(_databaseContext.getConnectionName());
    }
}

void
BotScript::dbClose() {
    _database.close();
}

bool
BotScript::dbIsOpen() const {
    return _database.isOpen();
}

bool
BotScript::dbIsOpenError() const {
    return _database.isOpenError();
}

QStringList
BotScript::dbTables(TableType type) const {
    return _database.tables(QSql::TableType(type));
}

QString
BotScript::dbLastDatabaseError() const {
    return QString("Database Text: %1, Driver Text: %2")
            .arg(_database.lastError().databaseText())
            .arg(_database.lastError().driverText());
}

bool
BotScript::dbIsDatabaseValid() const {
    return _database.isValid();
}

bool
BotScript::dbTransaction() {
    return _database.transaction();
}

bool
BotScript::dbCommit() {
    return _database.commit();
}

bool
BotScript::dbRollback() {
    return _database.rollback();
}

void
BotScript::dbSetDatabaseName(const QString &databaseName) {
    _databaseContext.databaseName = databaseName;
}

void
BotScript::dbSetUserName(const QString &userName) {
    _databaseContext.userName = userName;
}

void
BotScript::dbSetPassword(const QString &password) {
    _databaseContext.password = password;
}


void
BotScript::dbSetHostName(const QString &hostName) {
    _databaseContext.hostName = hostName;
}

void
BotScript::dbSetPort(int port) {
    _databaseContext.port = port;
}

void
BotScript::dbSetConnectOptions(const QString &options) {
    _database.setConnectOptions(options);
}

QString
BotScript::dbDatabaseName() const {
    return _databaseContext.databaseName;
}

QString
BotScript::dbUserName() const {
    return _databaseContext.userName;
}

QString
BotScript::dbHostName() const {
    return _databaseContext.hostName;
}

QString
BotScript::dbDriverName() const {
    return _databaseContext.driverName;
}

int
BotScript::dbPort() const {
    return _databaseContext.port;
}

QString
BotScript::dbConnectOptions() const {
    return _database.connectOptions();
}

QString
BotScript::dbConnectionName() const {
    return _databaseContext.getConnectionName();
}

void
BotScript::dbSetNumericalPrecisionPolicy(const NumericalPrecisionPolicy &precisionPolicy) {
    _database.setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy(precisionPolicy));
}

BotScript::NumericalPrecisionPolicy
BotScript::dbNumericalPrecisionPolicy() const {
    return NumericalPrecisionPolicy(_database.numericalPrecisionPolicy());
}

void
BotScript::dbSetType(const QString &type) {
    _databaseContext.type = EnumUtils::keyToValue<SettingsParam::Database::DatabaseType>(type);
}

QStringList
BotScript::dbDrivers() {
    return QSqlDatabase::drivers();
}

bool
BotScript::dbIsDriverAvailable(const QString &name) {
    return QSqlDatabase::isDriverAvailable(name);
}

bool
BotScript::qryIsValid() const {
    return _query.isValid();
}

bool
BotScript::qryIsActive() const{
    return _query.isActive();
}

bool
BotScript::qryIsNull(int field) const {
    return _query.isNull(field);
}

bool BotScript::qryIsNull(const QString &name) const {
    return _query.isNull(name);
}

int
BotScript::qryAt() const {
    return _query.at();
}

QString
BotScript::qryLastQuery() const {
    return _query.lastQuery();
}

int
BotScript::qryNumRowsAffected() const {
    return _query.numRowsAffected();
}

QString
BotScript::qryLastError() const {
    return _query.lastError().text();
}

bool
BotScript::qryIsSelect() const {
    return _query.isSelect();
}

int BotScript::qrySize() const {
    return _query.size();
}

bool
BotScript::qryIsForwardOnly() const {
    return _query.isForwardOnly();
}

void
BotScript::qrySetForwardOnly(bool forward) {
    _query.setForwardOnly(forward);
}

QVariant
BotScript::qryValue(int i) const {
    return _query.value(i);
}

QVariant
BotScript::qryValue(const QString &name) const {
    return _query.value(name);
}

void
BotScript::qrySetNumericalPrecisionPolicy(BotScript::NumericalPrecisionPolicy precisionPolicy) {
    _query.setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy(precisionPolicy));
}

BotScript::NumericalPrecisionPolicy
BotScript::qryNumericalPrecisionPolicy() const {
    return BotScript::NumericalPrecisionPolicy(_query.numericalPrecisionPolicy());
}

bool
BotScript::qrySeek(int i, bool relative) {
    return _query.seek(i, relative);
}

bool
BotScript::qryNext() {
    return _query.next();
}

bool
BotScript::qryPrevious() {
    return _query.previous();
}

bool
BotScript::qryFirst() {
    return _query.first();
}

bool
BotScript::qryLast() {
    return _query.last();
}

void
BotScript::qryClear() {
    _query.clear();
}

bool
BotScript::qryPrepare(const QString &query) {
    return _query.prepare(query);
}

bool
BotScript::qryExec() {
    return _query.exec();
}

bool
BotScript::execBatch(BotScript::BatchExecutionMode mode) {
    return _query.execBatch(QSqlQuery::BatchExecutionMode(mode));
}

bool
BotScript::qryExec(const QString &query) {
    return _query.exec(query);
}

void
BotScript::qryBindValue(const QString &placeholder, const QVariant &value, ParamType type) {
    _query.bindValue(placeholder, value, QSql::ParamType(type));
}

void
BotScript::qryBindValue(int pos, const QVariant &value, ParamType type) {
    _query.bindValue(pos, value, QSql::ParamType(type));
}

void
BotScript::qryAddBindValue(const QVariant &val, ParamType type) {
    _query.addBindValue(val, QSql::ParamType(type));
}

QVariant
BotScript::qryBoundValue(const QString &placeholder) const {
    return _query.boundValue(placeholder);
}

QVariant
BotScript::qryBoundValue(int pos) const {
    return _query.boundValue(pos);
}

QMap<QString, QVariant>
BotScript::boundValues() const {
    return _query.boundValues();
}

QString
BotScript::qryExecutedQuery() const {
    return _query.executedQuery();
}

QVariant BotScript::qryLastInsertId() const {
    return _query.lastInsertId();
}

void
BotScript::qryFinish() {
    return _query.finish();
}

bool
BotScript::qryNextResult() {
    return _query.nextResult();
}

QMap<QString, QVariant>
BotScript::getScriptCommands() const {
    return _commands;
}

QString
BotScript::getScriptName() const {
    return _scriptName;
}

void BotScript::initAPI(const QString &botToken) {
    _discordAPI = QSharedPointer<DiscordAPI>(new DiscordAPI(botToken));
}

void
BotScript::setConnectionName() {
    _databaseContext.setConnectionName(_scriptName, _guildId);
}

void
BotScript::setConnectionName(const QString &scriptName, const QString &guildId) {
    _databaseContext.setConnectionName(scriptName, guildId);
}

QVariant
BotScript::cCreateMessage(const QVariant &contextVariant) {
    QSharedPointer<EventContext> context = QSharedPointer<EventContext>(new EventContext);

    SerializationUtils::fromVariant(*context.data(), contextVariant);

    return buildResponseVariant(_discordAPI->channelCreateMessage(context));
}

