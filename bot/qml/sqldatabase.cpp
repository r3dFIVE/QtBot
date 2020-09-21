#include "sqldatabase.h"

SqlDatabase::SqlDatabase(const SqlDatabase &other) {
    _database = other._database;

    _databaseContext = other._databaseContext;
}

SqlDatabase::SqlDatabase(const DatabaseContext &databaseContext) {
    _databaseContext = databaseContext;
}

SqlDatabase
&SqlDatabase::operator=(const SqlDatabase &other) {
    _database = other._database;

    _databaseContext = other._databaseContext;

    return *this;
}

bool
SqlDatabase::dbOpen() {
    closeExistingConnection();

    _database = QSqlDatabase::addDatabase(_databaseContext.driverName, _databaseContext.getConnectionName());

    _database.setHostName(_databaseContext.hostName);

    _database.setUserName(_databaseContext.userName);

    _database.setPassword(_databaseContext.password);

    _database.setDatabaseName(_databaseContext.databaseName);

    return _database.open();
}

void
SqlDatabase::closeExistingConnection() {
    if (QSqlDatabase::contains(_databaseContext.getConnectionName())) {

        _database.close();

        _database = QSqlDatabase();

        QSqlDatabase::removeDatabase(_databaseContext.getConnectionName());
    }
}

void
SqlDatabase::dbClose() {
    _database.close();
}

bool
SqlDatabase::dbIsOpen() const {
    return _database.isOpen();
}

bool
SqlDatabase::dbIsOpenError() const {
    return _database.isOpenError();
}

//QStringList
//SqlDatabase::dbTables(TableType type) const {
//    return _database.tables(QSql::TableType(type));
//}

//QString
//SqlDatabase::dbLastDatabaseError() const {
//    return QString("Database Text: %1, Driver Text: %2")
//            .arg(_database.lastError().databaseText())
//            .arg(_database.lastError().driverText());
//}

bool
SqlDatabase::dbIsDatabaseValid() const {
    return _database.isValid();
}

bool
SqlDatabase::dbTransaction() {
    return _database.transaction();
}

bool
SqlDatabase::dbCommit() {
    return _database.commit();
}

bool
SqlDatabase::dbRollback() {
    return _database.rollback();
}

void
SqlDatabase::dbSetDatabaseName(const QString &databaseName) {
    _databaseContext.databaseName = databaseName;
}

void
SqlDatabase::dbSetUserName(const QString &userName) {
    _databaseContext.userName = userName;
}

void
SqlDatabase::dbSetPassword(const QString &password) {
    _databaseContext.password = password;
}


void
SqlDatabase::dbSetHostName(const QString &hostName) {
    _databaseContext.hostName = hostName;
}

void
SqlDatabase::dbSetPort(int port) {
    _databaseContext.port = port;
}

void
SqlDatabase::dbSetConnectOptions(const QString &options) {
    _database.setConnectOptions(options);
}

QString
SqlDatabase::dbDatabaseName() const {
    return _databaseContext.databaseName;
}

QString
SqlDatabase::dbUserName() const {
    return _databaseContext.userName;
}

QString
SqlDatabase::dbHostName() const {
    return _databaseContext.hostName;
}

QString
SqlDatabase::dbDriverName() const {
    return _databaseContext.driverName;
}

int
SqlDatabase::dbPort() const {
    return _databaseContext.port;
}

QString
SqlDatabase::dbConnectOptions() const {
    return _database.connectOptions();
}

QString
SqlDatabase::dbConnectionName() const {
    return _databaseContext.getConnectionName();
}

//void
//SqlDatabase::dbSetNumericalPrecisionPolicy(const NumericalPrecisionPolicy &precisionPolicy) {
//    _database.setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy(precisionPolicy));
//}

//SqlDatabase::NumericalPrecisionPolicy
//SqlDatabase::dbNumericalPrecisionPolicy() const {
//    return NumericalPrecisionPolicy(_database.numericalPrecisionPolicy());
//}

//void
//SqlDatabase::dbSetType(const QString &type) {
//    _databaseContext.type = EnumUtils::keyToValue<SettingsParam::Database::DatabaseType>(type);
//}

QStringList
SqlDatabase::dbDrivers() {
    return QSqlDatabase::drivers();
}

bool
SqlDatabase::dbIsDriverAvailable(const QString &name) {
    return QSqlDatabase::isDriverAvailable(name);
}

void
SqlDatabase::setConnectionName() {
    _databaseContext.setConnectionName(_databaseContext.scriptName, _databaseContext.guildId);
}


void
SqlDatabase::setConnectionName(const QString &scriptName, const QString &guildId) {
    _databaseContext.setConnectionName(scriptName, guildId);
}

QSqlDatabase
SqlDatabase::getDatabase() {
    return _database;
}
