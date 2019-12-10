#include <QCoreApplication>

#include <QSettings>
#include "bot.h"
#include "spdlog/spdlog.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QString str = "C:\\BMCProjects\\QtBot-master\\settings1234.ini";
    QSharedPointer<QSettings> settings(new QSettings(str, QSettings::IniFormat));

    Bot bot(settings);
    bot.run();

    return a.exec();
}


