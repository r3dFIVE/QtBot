#ifndef SCRIPTREGISTRAR_H
#define SCRIPTREGISTRAR_H

#include "botscript.h"

#include <QObject>
#include <QSharedPointer>

typedef QPair<QString, QSharedPointer<BotScript>> BotMapping;

class ScriptRegistrar : public QObject
{
    Q_OBJECT

    QMap<QString, QPair<QString, QSharedPointer<BotScript>>> _registry;

public:
    explicit ScriptRegistrar(QObject *parent = nullptr);
    ~ScriptRegistrar() {}
    ScriptRegistrar(const ScriptRegistrar &other) { Q_UNUSED(other)}

    void setRegistry(const QMap<QString, QPair<QString, QSharedPointer<BotScript>>> &registry);

    QPair<QString, QSharedPointer<BotScript> > getScript(const QString &command);

};

Q_DECLARE_METATYPE(ScriptRegistrar)

#endif // SCRIPTREGISTRAR_H
