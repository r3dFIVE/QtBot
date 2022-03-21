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

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

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


class ScriptManager : public QObject
{
    Q_OBJECT

    EventHandler *_eventHandler;
    Logger *_logger;

    DatabaseContext _defaultDatabaseContext;
    QString _scriptDir;
    QStringList _coreCommandNames;
    QList<QFileInfo> _validScripts;
    QMap<QString, QList<QSharedPointer<IBotJob>>> _managedScripts;
    QMap<QString, QList<QSharedPointer<CommandBinding>>> _commandBindings;
    QMap<QString, QList<QSharedPointer<GatewayBinding>>> _gatewayBindings;
    QMap<QString, QList<QSharedPointer<TimedBinding>>> _timedBindings;
    QMap<QString, QString> _scriptNamesByCommand;
    QMap<QString, QMap<QString, QString> > _functionNameByEventNameByScriptName;

    bool isBotScript(const QString &fileName);
    void validateScripts();
    bool validateScriptCommandName(const QString &command, const QString &fileName);
    void addCoreCommands(GuildEntity &guildEntity);
    void addQmlFactory(QSharedPointer<QQmlEngine> engine);
    void buildValidBotScripts(GuildEntity &guildEntity);
    void buildBotScript(const QFileInfo &fileInfo, GuildEntity &guildEntity);
    void namingConflict(const QString &command, const QString &fileName);
    bool validateScriptName(const QString &scriptName, const QString &fileName);

    template <class T>
    QSharedPointer<T> buildBinding(QSharedPointer<T> t, BotScript* botScript) {
            QString functionName = t->getFunctionMapping().first;
            IBotJob::FunctionMapping functionMapping = qMakePair(functionName, botScript);
            QSharedPointer<T> newBinding = QSharedPointer<T>(new T(*t));
            newBinding->setFunctionMapping(functionMapping);
            return newBinding;
    }

    void validate(const QFileInfo &fileInfo);
    bool validateScriptCommands(BotScript *botScript, const QFileInfo &fileInfo);
    bool validateCommandBinding(BotScript *botScript, const QJsonValue &binding);
    bool validateGatewayBinding(BotScript *botScript, const QJsonValue &binding);
    bool validateTimedBinding(BotScript *botScript, const QJsonValue &binding);

public:
    ScriptManager(EventHandler *eventHandler);
    ~ScriptManager();

    void init(const QString &botToken, const QString &scriptDir);

public slots:
    void buildScripts(QSharedPointer<GuildEntity> guild, bool validate);

signals:
    void guildReady(QSharedPointer<GuildEntity> guild);
};

#endif // SCRIPTMANAGER_H
