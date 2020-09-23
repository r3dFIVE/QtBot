#ifndef BOTSCRIPT_H
#define BOTSCRIPT_H

#include <QMap>
#include <QObject>
#include <QQmlEngine>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
#include <QVariantMap>

#include "routes/discordapi.h"

#include "databasecontext.h"
#include "ibotjob.h"
#include "payloads/eventcontext.h"
#include "qml/file.h"
#include "util/globals.h"

class TimedBinding;

class BotScript : public IBotJob
{
    Q_OBJECT

    Logger *_logger;

    DatabaseContext _databaseContext;
    QJsonArray _eventBindingsJson;
    QMap<QString, QVariant> _commands;
    QMutex _runLock;
    QSharedPointer<DiscordAPI> _discordAPI;
    QSharedPointer<QQmlEngine> _engine;
    QSqlDatabase _database;
    QSqlQuery _query;
    QString _scriptName;
    QString _botToken;

    void setScriptCommands(const QMap<QString, QVariant> &commands);
    void setEventBindingsJson(const QJsonArray &eventBindings);

    Q_PROPERTY(QString name READ getScriptName WRITE setScriptName REQUIRED)
    Q_PROPERTY(QMap commands READ getScriptCommands WRITE setScriptCommands)
    Q_PROPERTY(QJsonArray event_bindings READ getEventBindingsJson WRITE setEventBindingsJson)

public:
    BotScript();
    BotScript(const BotScript &other);
    ~BotScript();
    BotScript &operator=(const BotScript &other);

    DatabaseContext getDatabaseContext() const;
    QMap<QString, QVariant> getScriptCommands() const;
    QJsonArray getEventBindingsJson() const;
    QString getScriptName() const;
    QString findFunctionMapping(const QString &command) const;
    void setDatabaseContext(const DatabaseContext &databaseContext);
    void setEngine(QSharedPointer<QQmlEngine> engine);
    void setScriptName(const QString &scriptName);

    bool invokable() override;
    void execute(const QByteArray &command, const EventContext &message) override;


    /*
     *  General API related functions
     */

    Q_INVOKABLE void logTrace(QString event);
    Q_INVOKABLE void logInfo(QString event);
    Q_INVOKABLE void logDebug(QString event);
    Q_INVOKABLE void logWarning(QString event);
    Q_INVOKABLE void logCritical(QString event);
    Q_INVOKABLE void logFatal(QString event);
    Q_INVOKABLE void pause(int ms);
    Q_INVOKABLE void queueTimedEvent(const QVariant &timedBindingVariant);

    /*
     *  DiscordAPI related functions
     */

    /*
     *  Channel API functions.
     *  https://discord.com/developers/docs/resources/channel
     */

    Q_INVOKABLE QVariant cGetChannel(const QVariant &context);
    Q_INVOKABLE QVariant cModifyChannel(const QVariant &context);
    Q_INVOKABLE QVariant cDeleteChannel(const QVariant &context);
    Q_INVOKABLE QVariant cGetChannelMessages(const QVariant &context);
    Q_INVOKABLE QVariant cGetChannelMessage(const QVariant &context);
    Q_INVOKABLE QVariant cCreateMessage(const QVariant &context);
    Q_INVOKABLE QVariant cCrosspostMessage(const QVariant &context);
    Q_INVOKABLE QVariant cCreateReaction(const QVariant &context);
    Q_INVOKABLE QVariant cDeleteOwnReaction(const QVariant &context);
    Q_INVOKABLE QVariant cDeleteUserReaction(const QVariant &context);
    Q_INVOKABLE QVariant cGetReactions(const QVariant &context);
    Q_INVOKABLE QVariant cDeleteAllReactions(const QVariant &context);
    Q_INVOKABLE QVariant cDeleteAllReactionsForEmoji(const QVariant &context);
    Q_INVOKABLE QVariant cEditMessage(const QVariant &context);
    Q_INVOKABLE QVariant cDeleteMessage(const QVariant &context);
    Q_INVOKABLE QVariant cBulkDeleteMessages(const QVariant &context);
    Q_INVOKABLE QVariant cEditChannelPermissions(const QVariant &context);
    Q_INVOKABLE QVariant cGetChannelInvites(const QVariant &context);
    Q_INVOKABLE QVariant cCreateChannelInvite(const QVariant &context);
    Q_INVOKABLE QVariant cFollowNewsChannel(const QVariant &context);
    Q_INVOKABLE QVariant cTriggerTypingIndicator(const QVariant &context);
    Q_INVOKABLE QVariant cGetPinnedMessages(const QVariant &context);
    Q_INVOKABLE QVariant cAddPinnedChannelMessage(const QVariant &context);
    Q_INVOKABLE QVariant cDeletePinnedChannelMessage(const QVariant &context);
    Q_INVOKABLE QVariant cGroupDmAddRecipient(const QVariant &context);
    Q_INVOKABLE QVariant cGroupDmRemoveRecipient(const QVariant &context);


signals:
    void timedBindingReady(const QString &guildId, QSharedPointer<TimedBinding> timedBinding);
};

Q_DECLARE_METATYPE(BotScript)

#endif // BOTSCRIPT_H
