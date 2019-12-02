#include <QCoreApplication>

#include <QSettings>
#include "bot.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str = "C:\\BMCProjects\\QtBot-master\\settings.ini";
    QSharedPointer<QSettings> settings(new QSettings(str, QSettings::IniFormat));

    Bot bot(settings);
    bot.run();

    return a.exec();
}


