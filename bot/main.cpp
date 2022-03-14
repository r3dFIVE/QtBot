/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QCommandLineParser>
#include <QDir>
#include <csignal>

#include "bot.h"

void
sigHandler(int s) {
    LogFactory::getLogger("Bot")->info(Bot::GOODBYE);

    QCoreApplication::quit();
}


int main(int argc, char *argv[])
{
    std::signal(SIGINT, sigHandler);

    std::signal(SIGTERM, sigHandler);

    QCoreApplication app(argc, argv);

    QCoreApplication::setApplicationName("QtBot");

    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;

    parser.setApplicationDescription("QtBot - The extensible Qt Discord Bot!");

    parser.addVersionOption();

    parser.addHelpOption();

    QCommandLineOption targetSettingsFileOption(QStringList() << "s" << "settings-file",
              QCoreApplication::translate("main", "The absolute path to your settings file <settings-file>."),
              QCoreApplication::translate("main", "settings-file"));

    parser.addOption(targetSettingsFileOption);

    parser.process(app);

    QString targetSettingsFile;

    if (parser.isSet(targetSettingsFileOption)) {
        targetSettingsFile = parser.value(targetSettingsFileOption);

        if (!QFileInfo::exists(targetSettingsFile)) {
            qDebug().noquote() << QString("Target file %1 not found or invalid... exiting.\n")
                                  .arg(targetSettingsFile);

            exit(EXIT_FAILURE);
        }
    } else {
        QString settingsFile = "settings.ini";

        QString appPath = QCoreApplication::applicationDirPath();

        QString defaultSettingsFileWithRootPath = QString("%1/%2").arg(appPath, settingsFile);

        QString defaultSettingsFileWithConfigPath = QString("%1/config/%2").arg(appPath, settingsFile);

        if (QFileInfo::exists(defaultSettingsFileWithConfigPath)) {
            targetSettingsFile = defaultSettingsFileWithConfigPath;

        } else if (QFileInfo::exists(defaultSettingsFileWithRootPath)) {
            targetSettingsFile = defaultSettingsFileWithRootPath;

        } else {
            qDebug().noquote() << QString("Settings file not located in default locations: \"%1\" or \"%2\"... exiting.")
                                  .arg(defaultSettingsFileWithConfigPath, defaultSettingsFileWithRootPath);

            exit(EXIT_FAILURE);
        }
    }      

    Settings::load(targetSettingsFile);

    Bot bot;

    bot.run();

    return app.exec();
}


