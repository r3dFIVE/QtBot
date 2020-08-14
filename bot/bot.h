#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>

#include "logging/logfactory.h"
#include "gateway.h"
#include "botjob/scriptbuilder.h"
#include "util/settings.h"

class GuildEntity;
class ScriptBuilder;

class Bot : public QObject
{
    Q_OBJECT    

    QThread _gatewayThread;
    QThread _eventHandlerThread;
    QThread _entityManagerThread;

    Logger* _logger;
    ScriptBuilder *_factory;

public:

    Bot();
    ~Bot();
    Bot(const Bot &other) { Q_UNUSED(other) }
    void run(QSharedPointer<Settings> settings);

public slots:
    void loadCommands(QSharedPointer<GuildEntity> guild);
    void reloadAllCommands();

signals:
    void guildReady(QSharedPointer<GuildEntity> guild);
    void reloadAllAvailableGuilds();
};

Q_DECLARE_METATYPE(Bot)

#endif // BOT_H
