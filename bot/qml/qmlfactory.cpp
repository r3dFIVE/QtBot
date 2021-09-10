/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "http.h"
#include "httpmultipart.h"
#include "httppart.h"
#include "mongofind.h"
#include "mongoinsert.h"
#include "qmlfactory.h"

#include <QQmlEngine>
#include <QVariantMap>

#include "file.h"
#include "sqldatabase.h"
#include "sqlquery.h"
#include "qml/mongodb.h"
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

    } else if (typeName == "Http") {
        return new Http();

    } else if (typeName == "HttpPart") {
        return new HttpPart();

    } else if (typeName == "HttpMultiPart") {
        return new HttpMultiPart();

    } else if (typeName == "MongoDB") {
        return new MongoDB(_databaseContext);

    } else if (typeName == "MongoFind") {
        return new MongoFind();

    } else if (typeName == "MongoInsert") {
        return new MongoInsert();

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

void
QmlFactory::buildQmlFactory(QSharedPointer<QQmlEngine> engine, const DatabaseContext &context) {
    engine->installExtensions(QQmlEngine::ConsoleExtension);

    QJSValue factory = engine->newQObject(new QmlFactory(context));

    engine->globalObject().setProperty("_factory", factory);

    engine->evaluate("function File(path, mode = 1) { return _factory.createObject(\"File\", { filePath: path, openMode: mode }); }");

    engine->evaluate("function Http() { return _factory.createObject(\"Http\", {}); }");

    engine->evaluate("function HttpPart() { return _factory.createObject(\"HttpPart\", {}); }");

    engine->evaluate("function HttpMultiPart() { return _factory.createObject(\"HttpMultiPart\", {}); }");

    engine->evaluate("function SqlDatabase() { return _factory.createObject(\"SqlDatabase\", {}); }");

    engine->evaluate("function MongoDB() { return _factory.createObject(\"MongoDB\", {}); }");

    engine->evaluate("function MongoFind() { return _factory.createObject(\"MongoFind\", {}); }");

    engine->evaluate("function MongoInsert() { return _factory.createObject(\"MongoInsert\", {}); }");

    engine->evaluate("function SqlQuery(db) { return _factory.createObject(\"SqlQuery\", { database: db }); }");

    engine->evaluate("function SqlError(error) { return _factory.createObject(\"SqlError\", { sqlError: error }); }");

    engine->evaluate("function SqlRecord() { return _factory.createObject(\"SqlRecord\", {}); }");

    engine->evaluate("function SqlField() { return _factory.createObject(\"SqlField\", {}); }");
}

