#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>
#include "gatewayconnection.h"

class Bot : public QObject
{
    Q_OBJECT

public:
    Bot(QSharedPointer<QSettings> settings);
    void run();

private:
    QThread m_gatewayThread;
    QThread m_messageHandlerThread;
    QSharedPointer<QSettings> m_settings;

    QUrl buildConnectionUrl();
};

#endif // BOT_H
