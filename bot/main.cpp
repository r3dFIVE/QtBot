#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QMetaEnum>
#include <QObject>

#include "bot.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "C:\\workspace\\settings.ini";

    if(!(QFileInfo::exists(path))) {
        qDebug().noquote() << QString("Settings file %1 does not exist. . . exiting.\n").arg(path);
        exit(1);
    }    

    QSharedPointer<Settings> settings = QSharedPointer<Settings>(new Settings(path));

    Bot bot;
    bot.run(settings);

    return a.exec();
}


