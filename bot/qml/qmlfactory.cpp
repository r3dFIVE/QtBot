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

#include "xmlquery.h"
#include "mongodeleteoptions.h"
#include "mongoupdateoptions.h"
#include "qmlfactory.h"
#include "domparser.h"

#include <QQmlEngine>
#include <QVariantMap>

#include "http.h"
#include "httpmultipart.h"
#include "httppart.h"
#include "mongofindoptions.h"
#include "mongoinsertoptions.h"
#include "file.h"
#include "sqldatabase.h"
#include "sqlquery.h"
#include "qml/mongodb.h"
#include "routes/discordapi.h"
#include "payloads/embed.h"
#include "payloads/embedauthor.h"
#include "payloads/embedfooter.h"
#include "payloads/embedmedia.h"


QmlFactory::QmlFactory(const DatabaseContext &databaseContext, QObject *parent) : QObject(parent)  {
    _databaseContext = databaseContext;
 }

QObject*
QmlFactory::createObject(const QString& typeName, const QVariantMap& arguments) {
    if (typeName == "File"){
        return createFile(arguments);

    } else if (typeName == "Embed") {
        return createEmbed(arguments);

    } else if (typeName == "EmbedField") {
        return createEmbedField(arguments);

    } else if (typeName == "EmbedAuthor") {
        return createEmbedAuthor(arguments);

    } else if (typeName == "EmbedFooter") {
        return createEmbedFooter(arguments);

    } else if (typeName == "EmbedMedia") {
        return createEmbedMedia(arguments);

    } else if (typeName == "Http") {
        return new Http();

    } else if (typeName == "HttpPart") {
        return new HttpPart();

    } else if (typeName == "HttpMultiPart") {
        return new HttpMultiPart();

    } else if (typeName == "MongoDB") {
        return new MongoDB(_databaseContext);

    } else if (typeName == "MongoFindOptions") {
        return new MongoFindOptions();

    } else if (typeName == "MongoInsertOptions") {
        return new MongoInsertOptions();

    } else if (typeName == "MongoUpdateOptions") {
        return new MongoUpdateOptions();

    } else if (typeName == "MongoDeleteOptions") {
        return new MongoDeleteOptions();

    } else if (typeName == "SqlDatabase") {
        return new SqlDatabase(_databaseContext);

    } else if (typeName == "SqlQuery") {
        return createSqlQuery(arguments);

    } else if (typeName == "XMLQuery") {
        return new XMLQuery();

    } else if (typeName == "DOMParser") {
        return new DOMParser();
    }

    return nullptr;
}

void
QmlFactory::buildQmlFactory(QSharedPointer<QQmlEngine> engine, const DatabaseContext &context) {
    engine->installExtensions(QQmlEngine::ConsoleExtension);

    QJSValue factory = engine->newQObject(new QmlFactory(context));

    engine->globalObject().setProperty("_factory", factory);

    engine->evaluate("function TempFile(path, mode = 1) { return _factory.createObject(\"TempFile\", { filePath: path, openMode: mode }); }");

    engine->evaluate("function File(path, mode = 1) { return _factory.createObject(\"File\", { filePath: path, openMode: mode }); }");

    engine->evaluate("function Http() { return _factory.createObject(\"Http\", {}); }");

    engine->evaluate("function XMLQuery() { return _factory.createObject(\"XMLQuery\", {}); }");

    engine->evaluate("function Embed(title, description, url, color) { return _factory.createObject(\"Embed\", {title: title, description: description, url: url, color: color}); }");

    engine->evaluate("function EmbedField(name, value, inline) { return _factory.createObject(\"EmbedField\", {name: name, value: value, inline: inline}); }");

    engine->evaluate("function EmbedAuthor(name, iconUrl, url) { return _factory.createObject(\"EmbedAuthor\", {name: name, iconUrl: iconUrl, url: url,}); }");

    engine->evaluate("function EmbedFooter(text, iconUrl) { return _factory.createObject(\"EmbedFooter\", {text: text, iconUrl: iconUrl}); }");

    engine->evaluate("function EmbedMedia(url, height, width) { return _factory.createObject(\"EmbedMedia\", {url: url, height: height, width: width}); }");

    engine->evaluate("function HttpPart() { return _factory.createObject(\"HttpPart\", {}); }");

    engine->evaluate("function HttpMultiPart() { return _factory.createObject(\"HttpMultiPart\", {}); }");

    engine->evaluate("function SqlDatabase() { return _factory.createObject(\"SqlDatabase\", {}); }");

    engine->evaluate("function SqlQuery(db) { return _factory.createObject(\"SqlQuery\", { db: db }); }");

    engine->evaluate("function MongoDB() { return _factory.createObject(\"MongoDB\", {}); }");

    engine->evaluate("function MongoFindOptions() { return _factory.createObject(\"MongoFindOptions\", {}); }");

    engine->evaluate("function MongoInsertOptions() { return _factory.createObject(\"MongoInsertOptions\", {}); }");

    engine->evaluate("function MongoUpdateOptions() { return _factory.createObject(\"MongoUpdateOptions\", {}); }");

    engine->evaluate("function MongoDeleteOptions() { return _factory.createObject(\"MongoDeleteOptions\", {}); }");

    engine->evaluate("function DOMParser() { return _factory.createObject(\"DOMParser\", {}); }");
}

QObject*
QmlFactory::createFile(const QVariantMap& arguments) {
    QString filePath = arguments.value("filePath", "").toString();

    if (filePath.isEmpty()) {
        return new File;
    }

    OpenMode::Mode openMode =
            qvariant_cast<OpenMode::Mode>(arguments.value("openMode", OpenMode::ReadWrite));

    return new File(filePath, openMode);
}

QObject*
QmlFactory::createTempFile(const QVariantMap& arguments) {
    QString filePath = arguments.value("filePath", "").toString();

    if (filePath.isEmpty()) {
        return new TempFile;
    }

    OpenMode::Mode openMode =
            qvariant_cast<OpenMode::Mode>(arguments.value("openMode", OpenMode::ReadWrite));

    return new TempFile(filePath, openMode);
}

QObject*
QmlFactory::createSqlQuery(const QVariantMap& arguments) {
    SqlDatabase *db = qvariant_cast<SqlDatabase *>(arguments.value("db"));

    return new SqlQuery(db);
}

QObject*
QmlFactory::createEmbed(const QVariantMap& arguments) {
    QString title = arguments.value("title", "").toString();

    QString description = arguments.value("description", "").toString();

    QString url = arguments.value("url", "").toString();

    int color = arguments.value("color", "").toInt();

    return new Embed(title, description, url, color);
}

QObject*
QmlFactory::createEmbedField(const QVariantMap& arguments) {
    QString name = arguments.value("name", "").toString();

    QString value = arguments.value("value", "").toString();

    bool isInline = arguments.value("inline", false).toBool();

    return new EmbedField(name, value, isInline);
}

QObject*
QmlFactory::createEmbedAuthor(const QVariantMap& arguments) {
    QString text = arguments.value("name", "").toString();

    QString iconUrl = arguments.value("iconUrl", "").toString();

    QString url = arguments.value("url", "").toString();

    return new EmbedAuthor(text, iconUrl, url);
}

QObject*
QmlFactory::createEmbedFooter(const QVariantMap& arguments) {
    QString text = arguments.value("text", "").toString();

    QString iconUrl = arguments.value("iconUrl", "").toString();

    return new EmbedFooter(text, iconUrl);
}

QObject*
QmlFactory::createEmbedMedia(const QVariantMap& arguments) {
    QString url = arguments.value("url", "").toString();

    int height = arguments.value("height", 0).toUInt();

    int width = arguments.value("width", 0).toUInt();

    return new EmbedMedia(url, height, width);
}
