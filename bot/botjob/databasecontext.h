#ifndef DATABASECONTEXT_H
#define DATABASECONTEXT_H

#include <QSharedPointer>

#include "util/settings.h"


class DatabaseContext
{       
    QString _connectionName;

public:
    int port;
    int type;
    QString hostName;
    QString userName;
    QString password;
    QString databaseName;
    QString driverName;
    QString scriptName;
    QString guildId;

    DatabaseContext() {}
    DatabaseContext(QSharedPointer<Settings> settings);
    DatabaseContext(const DatabaseContext &other);
    ~DatabaseContext() {}
    void setConnectionName(const QString &scriptName, const QString &guildId);
    QString getConnectionName() const;
};

#endif // DATABASECONTEXT_H
