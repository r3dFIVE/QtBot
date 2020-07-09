#include "qml/botscript.h"

#include "util/jsonutils.h"

#include <payloads/jsonserializable.h>
#include <payloads/message.h>

#include <QQmlComponent>



void
BotScript::setCommands(QMap<QString, QVariant> commands) {
    _commands = commands;
}

QMap<QString, QVariant>
BotScript::commands() const {
    return _commands;
}

void
BotScript::setName(const QString &name) {
    _name = name;
}

QString
BotScript::name() const {
    return _name;
}

BSqlDatabase
BotScript::database() const {
    return _database;
}

void
BotScript::setDatabase(const BSqlDatabase &database) {
    _database = database;
}

QString
BotScript::findMapping(const QString &command) const {
    return _commands[command].toString();
}

void
BotScript::execute(const QByteArray &command, const Message &message) {
    QVariant returnValue;

    QStringList args = message.content.toString().split(" ");

    QMetaObject::invokeMethod(this, command,
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, returnValue),
                              Q_ARG(QVariant, args));

    Message returned;
    JsonUtils::fromVariant(returned, returnValue);
    returned.setChannelId(message.getChannelId());

    LogFactory::getLogger()->debug(returned.content.toString());

    postResult(returned);
}


// TODO remove when httpclient moved to own event loop
void
BotScript::setToken(const QString &botToken) {
    _httpClient = QSharedPointer<HttpClient>(new HttpClient(botToken));
}

void
BotScript::postResult(const Message &message) {
    _httpClient->post(message, message.content.toString());
}
