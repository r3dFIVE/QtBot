#ifndef COMMANDREGISTRAR_H
#define COMMANDREGISTRAR_H

#include "util/icommand.h"

#include <QObject>
#include <QSharedPointer>


class CommandRegistrar : public QObject
{
    Q_OBJECT

    QMap<QString, ICommand::CommandMapping> _registry;

public:
    explicit CommandRegistrar(QObject *parent = nullptr);
    ~CommandRegistrar() {}
    CommandRegistrar(const CommandRegistrar &other) { Q_UNUSED(other)}

    void setRegistry(const QMap<QString, QPair<QString, QSharedPointer<ICommand>>> &registry);

    QPair<QString, QSharedPointer<ICommand> > getCommand(const QString &command);

};

Q_DECLARE_METATYPE(CommandRegistrar)

#endif // SCRIPTREGISTRAR_H
