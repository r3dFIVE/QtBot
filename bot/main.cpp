/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

    QString settingsPath = ".\\config\\settings.ini";

    bool exists;

    if (parser.isSet(targetFileOption)) {
        settingsPath = parser.value(targetFileOption);

        exists = QFileInfo::exists(settingsPath);
    } else {
        exists = QFileInfo::exists(settingsPath) || QFileInfo::exists(".\\settings.ini");
    }

    if(!exists) {
        qDebug().noquote() << QString("Settings file %1 not found... exiting.\n").arg(settingsPath);

        exit(EXIT_FAILURE);
    }    

    QSharedPointer<Settings> settings = QSharedPointer<Settings>(new Settings(settingsPath));

    LogFactory::init(settings);

    Bot bot;

    bot.run(settings);

    return qtbot.exec();
}


