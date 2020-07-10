#ifndef BOTSCRIPT_H
#define BOTSCRIPT_H

#include "bsqldatabase.h"
#include "eventcontext.h"

#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <QVariantMap>
#include <httpclient.h>

#include <util/icommand.h>

class BotScript : public QObject, public ICommand
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName REQUIRED)
    QString _name;

    Q_PROPERTY(QMap commands READ getCommands WRITE setCommands REQUIRED)
    QMap<QString, QVariant> _commands;

    Q_PROPERTY(BSqlDatabase database READ getDatabase WRITE setDatabase)
    BSqlDatabase _database;

    QSharedPointer<HttpClient> _httpClient;

public:
    BotScript() {}
    BotScript(const QString &botToken) {
        _httpClient = QSharedPointer<HttpClient>(new HttpClient(botToken));
    }
    ~BotScript() {}
    BotScript(const BotScript &other) { Q_UNUSED(other) }

    void setCommands(QMap<QString, QVariant> commands);
    QMap<QString, QVariant> getCommands() const;
    void setName(const QString &name);
    QString getName() const;
    BSqlDatabase getDatabase() const;
    void setDatabase(const BSqlDatabase &database);
    void postResult(const Message &message);

    void setToken(const QString &botToken);

    QString findMapping(const QString &command) const;

    void execute(const QByteArray &command, const EventContext &message) override;
};

Q_DECLARE_METATYPE(BotScript)

#endif // BOTSCRIPT_H
