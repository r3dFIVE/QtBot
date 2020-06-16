#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>

#include "logging/logfactory.h"
#include "gateway.h"
#include "settings.h"


class Bot : public QObject
{
    Q_OBJECT

    QThread _gatewayThread;
    QThread _messageServiceThread;
    Logger* _logger;

public:
    Bot();
    void run(QSharedPointer<Settings> settings);

};

#endif // BOT_H
