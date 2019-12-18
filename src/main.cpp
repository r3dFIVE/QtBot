#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QMetaEnum>
#include <QObject>
#include "bot.h"
#include "spdlog/spdlog.h"
#include "globals.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "C:\\workspace\\QtBot\\settings.ini";

    if(!(QFileInfo::exists(path))) {
        qDebug().noquote() << QString("Settings file %1 does not exist. . . exiting.\n").arg(path);
        exit(1);
    }


    Bot bot(path);
    bot.run();

    return a.exec();
}


