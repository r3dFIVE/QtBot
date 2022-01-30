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

#ifndef QMLFACTORY_H
#define QMLFACTORY_H

#include <QQmlEngine>
#include <QObject>
#include <QSharedPointer>

#include "botjob/databasecontext.h"


class QmlFactory : public QObject
{
    Q_OBJECT

    DatabaseContext _databaseContext;

    QObject *createFile(const QVariantMap& arguments);
    QObject *createTempFile(const QVariantMap& arguments);
    QObject *createSqlQuery(const QVariantMap& arguments);
    QObject *createEmbed(const QVariantMap &arguments);
    QObject *createEmbedField(const QVariantMap &arguments);
    QObject *createEmbedAuthor(const QVariantMap& arguments);
    QObject *createEmbedFooter(const QVariantMap& arguments);
    QObject *createEmbedMedia(const QVariantMap& arguments);

public:
    QmlFactory(const DatabaseContext &context, QObject *parent = nullptr);

    Q_INVOKABLE QObject *createObject(const QString& typeName, const QVariantMap& arguments);

    static void buildQmlFactory(QSharedPointer<QQmlEngine> engine, const DatabaseContext &context);
};

#endif // QMLFACTORY_H
