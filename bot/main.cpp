#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QCommandLineParser>

#include "bot.h"


int main(int argc, char *argv[])
{
    QCoreApplication qtbot(argc, argv);

    QCoreApplication::setApplicationName("QtBot");

    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;

    parser.setApplicationDescription("QtBot - The extensible Qt Discord Bot!");

    parser.addVersionOption();

    parser.addHelpOption();

    QCommandLineOption targetFileOption(QStringList() << "s" << "settings-file",
              QCoreApplication::translate("main", "The absolute path to your settings file <settings-file>."),
              QCoreApplication::translate("main", "settings-file"));

    parser.addOption(targetFileOption);

    parser.process(qtbot);

    QString path;

    if (parser.isSet(targetFileOption)) {
        path = parser.value(targetFileOption);
    } else {
        path = ".\\settings.ini";
    }

    if(!(QFileInfo::exists(path))) {
        qDebug().noquote() << QString("Settings file %1 does not exist... exiting.\n").arg(path);
        exit(1);
    }    

    QSharedPointer<Settings> settings = QSharedPointer<Settings>(new Settings(path));

    LogFactory::init(settings);

    Bot bot;

    bot.run(settings);

    return qtbot.exec();
}


