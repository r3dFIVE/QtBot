#ifndef BOTSCRIPT_H
#define BOTSCRIPT_H

#include "bsqldatabase.h"

#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <QVariantMap>
#include <httpclient.h>

class BotScript : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName REQUIRED)
    QString _name;

    Q_PROPERTY(QMap commands READ commands WRITE setCommands REQUIRED)
    QMap<QString, QVariant> _commands;

    Q_PROPERTY(BSqlDatabase database READ database WRITE setDatabase)
    BSqlDatabase _database;

    QSharedPointer<HttpClient> _httpClient;

public:
    BotScript() {}
    BotScript(const QString &botToken) {
        _httpClient = QSharedPointer<HttpClient>(new HttpClient(botToken));
    }
    ~BotScript() {}
    BotScript(const BotScript &b) { Q_UNUSED(b) }

    void setCommands(QMap<QString, QVariant> commands);
    QMap<QString, QVariant> commands() const;
    void setName(const QString &name);
    QString name() const;
    BSqlDatabase database() const;
    void setDatabase(const BSqlDatabase &database);
    void postResult(const Message &message);

    void setToken(const QString &botToken);

    QString findMapping(const QString &command) const;

    void execute(const QByteArray &command, const Message &message);
};

Q_DECLARE_METATYPE(BotScript)

#endif // BOTSCRIPT_H
