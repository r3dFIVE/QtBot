/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "qmlfactory.h"

#include <QQmlEngine>
#include <QVariantMap>

#include "file.h"
#include "sqldatabase.h"
#include "sqlquery.h"
#include "routes/discordapi.h"


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
        return new SqlField;

    } else if (typeName == "SqlRecord") {
        return new SqlRecord;

    } else if (typeName == "SqlError") {
        SqlError sqlError = qvariant_cast<SqlError>(arguments.value("sqlError"));

        return new SqlError(sqlError);
    }

    return nullptr;
}
