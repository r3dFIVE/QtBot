#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QThread>
#include "gatewayconnection.h"

class Bot : public QObject
{
    Q_OBJECT

private:
    QThread _gatewayThread;
    QThread _messageHandlerThread;

private slots:


public:
    Bot();
    void run();


};

#endif // BOT_H
