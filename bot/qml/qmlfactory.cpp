#include "qmlfactory.h"

#include <QQmlEngine>
#include <QVariantMap>

#include "file.h"
#include "sqldatabase.h"
#include "sqlquery.h"


QmlFactory::QmlFactory(const DatabaseContext &databaseContext) {
    _databaseContext = databaseContext;
}

QObject*
QmlFactory::createObject(const QString& typeName, const QVariantMap& arguments) {
    if (typeName == "File"){
        QString filePath = arguments.value("filePath").toString();

        OpenMode::Mode openMode =
                qvariant_cast<OpenMode::Mode>(arguments.value("openMode", OpenMode::ReadWrite));

        return new File(filePath, openMode);

    } else if (typeName == "SqlDatabase") {
        return new SqlDatabase(_databaseContext);

    } else if (typeName == "SqlQuery") {
        SqlDatabase *db = qvariant_cast<SqlDatabase *>(arguments.value("database"));

        return new SqlQuery(db);

    } else if (typeName == "SqlField") {
        return new SqlField();

    } else if (typeName == "SqlRecord") {
        return new SqlRecord();

    } else if (typeName == "SqlError") {
        return new SqlError();
    }

    Q_ASSERT(false);

    return nullptr;
}
