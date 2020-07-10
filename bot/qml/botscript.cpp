#include "qml/botscript.h"
#include "util/serializationutils.h"
#include "qml/eventcontext.h"
#include "eventcontext.h"

#include <QQmlComponent>


void
BotScript::setCommands(QMap<QString, QVariant> commands) {
    _commands = commands;
}

QMap<QString, QVariant>
BotScript::getCommands() const {
    return _commands;
}

void
BotScript::setName(const QString &name) {
    _name = name;
}

QString
BotScript::getName() const {
    return _name;
}

BSqlDatabase
BotScript::getDatabase() const {
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
BotScript::execute(const QByteArray &command, const EventContext &context) {
    QVariant returnValue;

    QStringList args = context.content.toString().split(" ");

    QMetaObject::invokeMethod(this, command,
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, returnValue),
                              Q_ARG(QVariant, args));

    Message returned;
    SerializationUtils::fromVariant(returned, returnValue);
    returned.channel_id = context.channel_id;

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
