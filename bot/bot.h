#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>

#include "logging/logfactory.h"
#include "gateway.h"
#include "qml/registrarfactory.h"
#include "qml/commandregistrar.h"
#include "util/settings.h"

class RegistrarFactory;

class Bot : public QObject
{
    Q_OBJECT    

    QThread _gatewayThread;
    QThread _eventHandlerThread;

    Logger* _logger;
    RegistrarFactory *_factory;

public:
    Bot();
    ~Bot() { delete _factory; }
    Bot(const Bot &other) { Q_UNUSED(other) }
    void run(QSharedPointer<Settings> settings);

public slots:
    void loadRegistrar();

signals:
    void registrarReady(QSharedPointer<CommandRegistrar> registrar);
};

Q_DECLARE_METATYPE(Bot)

#endif // BOT_H
