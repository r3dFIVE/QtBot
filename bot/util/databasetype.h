#ifndef DATABASETYPE_H
#define DATABASETYPE_H

#include <QObject>

namespace DatabaseType {
    Q_NAMESPACE

    enum Type {
        QMONGODB = 0,
        QSQLITE,
        QMYSQL

    };
    Q_ENUM_NS(Type)
}

#endif // DATABASETYPE_H
