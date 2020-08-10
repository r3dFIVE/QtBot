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

    DatabaseContext() {}
    DatabaseContext(QSharedPointer<Settings> settings);
    ~DatabaseContext() {}
    void setConnectionName(const QString &scriptName, const QString &guildId);
    QString getConnectionName() const;
};

#endif // DATABASECONTEXT_H
