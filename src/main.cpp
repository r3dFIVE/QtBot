#include <QCoreApplication>
#include "bot.h"

#ifdef __cplusplus
extern "C"{
#endif

#include <sodium.h>
#include <opus.h>

#ifdef __cplusplus
}
#endif

#include "payloads/gatewaypayload.h"
#include "lockingdeque.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread botThread;
    Bot *bot = new Bot();
    QObject::connect(&botThread, &QThread::started, bot, &Bot::run);
    bot->moveToThread(&botThread);
    botThread.start();


    return a.exec();
}


