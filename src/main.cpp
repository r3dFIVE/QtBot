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
        // TODO - clean up message;
        qDebug() << "Settings file not found. . . exiting.\n";
        exit(1);
    }


    QSharedPointer<QSettings> settings(new QSettings(path, QSettings::IniFormat));

    Bot bot(settings);
    bot.run();

    return a.exec();
}


