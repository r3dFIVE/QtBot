#include "bsqldatabase.h"

#include <QSqlError>
#include <QDebug>


const char *BSqlDatabase::defaultConnection = const_cast<char *>("qt_sql_default_connection");

BSqlDatabase::BSqlDatabase(const BSqlDatabase &other) {
    _database = other._database;
    _query = other._query;
}

BSqlDatabase
&BSqlDatabase::operator=(const BSqlDatabase &other) {
    _database = other._database;
    _query = other._query;
    return *this;
}

bool
BSqlDatabase::setDatabaseConnection(const QSqlDatabase &database) {
    if (database.isValid()) {
        _query = QSqlQuery(database);
        return true;
    }

    qDebug() << database.lastError();
    return false;
}

bool
BSqlDatabase::open() {
    return _database.open();
}

bool
BSqlDatabase::open(const QString &userName, const QString &password) {
    return _database.open(userName, password);
}

void
BSqlDatabase::close() {
    _database.close();
}

bool
BSqlDatabase::isOpen() const {
    return _database.isOpen();
}

bool
BSqlDatabase::isOpenError() const {
    return _database.isOpenError();
}

QStringList
BSqlDatabase::tables(TableType type) const {
    return _database.tables(QSql::TableType(type));
}

QString
BSqlDatabase::lastDatabaseError() const {
    return QString("Database Text: %1, Driver Text: %2")
            .arg(_database.lastError().databaseText())
            .arg(_database.lastError().driverText());
}

bool
BSqlDatabase::isDatabaseValid() const {
    return _database.isValid();
}

bool
BSqlDatabase::transaction() {
    return _database.transaction();
}

bool
BSqlDatabase::commit() {
    return _database.commit();
}

bool
BSqlDatabase::rollback() {
    return _database.rollback();
}

void
BSqlDatabase::setDatabaseConnection(const QString &name) {
    setDatabaseConnection(QSqlDatabase::database(name));
}

void
BSqlDatabase::setDatabaseName(const QString &databaseName) {
    _database.setDatabaseName(databaseName);
}

void
BSqlDatabase::setUserName(const QString &userName) {
    _database.setUserName(userName);
}

void
BSqlDatabase::setPassword(const QString &password) {
    _database.setPassword(password);
}


void
BSqlDatabase::setHostName(const QString &hostName) {
    _database.setHostName(hostName);
}

void
BSqlDatabase::setPort(int port) {
    _database.setPort(port);
}

void
BSqlDatabase::setConnectOptions(const QString &options) {
    _database.setConnectOptions(options);
}

QString
BSqlDatabase::databaseName() const {
    return _database.databaseName();
}

QString
BSqlDatabase::userName() const {
    return _database.userName();
}

QString
BSqlDatabase::password() const {
    return _database.password();
}

QString
BSqlDatabase::hostName() const {
    return _database.hostName();
}

QString
BSqlDatabase::driverName() const {
    return _database.driverName();
}

int
BSqlDatabase::port() const {
    return _database.port();
}

QString
BSqlDatabase::connectOptions() const {
    return _database.connectOptions();
}

QString
BSqlDatabase::connectionName() const {
    return _database.connectionName();
}

void
BSqlDatabase::setNumericalPrecisionPolicy(NumericalPrecisionPolicy precisionPolicy) {
    _database.setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy(precisionPolicy));
}

BSqlDatabase::NumericalPrecisionPolicy
BSqlDatabase::numericalPrecisionPolicy() const {
    return NumericalPrecisionPolicy(_database.numericalPrecisionPolicy());
}

bool
BSqlDatabase::addDatabase(const QString &type, const QString &connectionName) {
    _database = QSqlDatabase::addDatabase(type, connectionName);
    return setDatabaseConnection(_database);
}

bool
BSqlDatabase::database(const QString &connectionName, bool open) {
    _database = QSqlDatabase::database(connectionName, open);
    return setDatabaseConnection(_database);
}

void
BSqlDatabase::removeDatabase(const QString &connectionName) {
    QSqlDatabase::removeDatabase(connectionName);
}

bool
BSqlDatabase::contains(const QString &connectionName) {
    return QSqlDatabase::contains(connectionName);
}

QStringList
BSqlDatabase::drivers() {
    return QSqlDatabase::drivers();
}

QStringList
BSqlDatabase::connectionNames() {
    return QSqlDatabase::connectionNames();
}

bool
BSqlDatabase::isDriverAvailable(const QString &name) {
    return QSqlDatabase::isDriverAvailable(name);
}




QVariant
BSqlDatabase::value(int i) const {
    return _query.value(i);
}

QVariant
BSqlDatabase::value(const QString &name) const {
    return _query.value(name);
}


bool
BSqlDatabase::seek(int i, bool relative) {
    return _query.seek(i, relative);
}

bool
BSqlDatabase::next() {
    return _query.next();
}

bool
BSqlDatabase::prepare(const QString &query) {
    return _query.prepare(query);
}

bool
BSqlDatabase::exec() {
   return _query.exec();
}

bool
BSqlDatabase::exec(const QString &query) {
    return _query.exec(query);
}

void
BSqlDatabase::bindValue(const QString &placeholder, const QVariant &value, QSql::ParamType type) {
    _query.bindValue(placeholder, value, QSql::ParamType(type));
}

void
BSqlDatabase::bindValue(int pos, const QVariant &value, QSql::ParamType type) {
    _query.bindValue(pos, value, QSql::ParamType(type));
}



