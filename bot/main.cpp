#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QSettings>

#include "bot.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (!QSslSocket::supportsSsl()) {
        qDebug() << "OpenSSL libaries are not available, shutting down...";
        exit(1);
    }

    QString path = "C:\\workspace\\settings.ini";

    if(!(QFileInfo::exists(path))) {
        qDebug().noquote() << QString("Settings file %1 does not exist. . . exiting.\n").arg(path);
        exit(1);
    }    

    QSharedPointer<Settings> settings = QSharedPointer<Settings>(new Settings(path));

    LogFactory::init(settings);

    Bot bot;
    bot.run(settings);

    return a.exec();
}


