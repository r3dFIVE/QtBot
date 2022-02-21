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

#ifndef SCRIPTBUILDER_H
#define SCRIPTBUILDER_H

#include <QObject>
#include <QVariantMap>
#include <QDir>
#include <QFile>

#include "commandbinding.h"
#include "eventhandler.h"
#include "gatewaybinding.h"
#include "timedbinding.h"
#include "logging/logfactory.h"
#include "botjob/botscript.h"
#include "entity/guildentity.h"


class ScriptBuilder : public QObject
{
    Q_OBJECT

    EventHandler *_eventHandler;
    Logger *_logger;

    DatabaseContext _defaultDatabaseContext;
    QString _scriptDir;
    QStringList _coreCommandNames;
    QList<QFileInfo> _validScripts;
    QMap<QString, QList<CommandBinding> > _commandBindings;
    QMap<QString, QList<GatewayBinding> > _gatewayBindings;
    QMap<QString, QList<TimedBinding> > _timedBindings;
    QMap<QString, QString> _scriptNamesByCommand;
    QMap<QString, QMap<QString, QString> > _functionNameByEventNameByScriptName;

    bool isBotScript(const QString &fileName);
    void validateScripts();
    bool validateScriptCommandName(const QString &command, const QString &fileName);
    void addCoreCommands(GuildEntity &guildEntity);
    void addCommandBindings(GuildEntity &guildEntity, QSharedPointer<BotScript> botScript, const QString &fileName);
    void addGatewayBindings(GuildEntity &guildEntity, QSharedPointer<BotScript> botScript, const QString &fileName);
    void addTimedBindings(GuildEntity &guildEntity, QSharedPointer<BotScript> botScript, const QString &fileName);
    void addQmlFactory(QSharedPointer<QQmlEngine> engine);
    void buildValidBotScripts(GuildEntity &guildEntity);
    void buildBotScript(const QFileInfo &fileInfo, GuildEntity &guildEntity);
    void namingConflict(const QString &command, const QString &fileName);
    bool validateScriptName(const QString &scriptName, const QString &fileName);

    void validate(const QFileInfo &fileInfo);
    bool validateScriptCommands(QSharedPointer<BotScript> botScript, const QFileInfo &fileInfo);
    bool validateCommandBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding, const QFileInfo &fileInfo);
    bool validateGatewayBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding, const QFileInfo &fileInfo);
    bool validateTimedBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding, const QString &guildId, const QFileInfo &fileInfo);
public:
    ScriptBuilder(EventHandler *eventHandler);

    void init(const QString &botToken, const QString &scriptDir);

public slots:
    void buildScripts(QSharedPointer<GuildEntity> guild, bool validate);

signals:
    void guildReady(QSharedPointer<GuildEntity> guild);
};

#endif // SCRIPTBUILDER_H
