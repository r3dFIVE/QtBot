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

#ifndef SETTINGSSERVICE_H
#define SETTINGSSERVICE_H

#include <QMap>
#include <QObject>

class Settings
{
public:
    Settings(QString path);

    QVariant value(QString key);

private:
    QMap<QString, QVariant> _settings;
    QString _path;

    void parseSettingsFile();
    void validateSettings();
    void validateBotSettings();    
    void validateDatabaseSettings();
    void validateGatewaySettings();
    void validateLoggingSettings();
    void validateLogLevel(QString property, QString logLevel);
    void invalidDatabaseProperty [[ noreturn ]] (QString databaseType, QString propertyName);
    void invalidEnumValue [[ noreturn ]] (QString property, QString value, QMetaEnum metaEnum);
    bool isComment(QString);
    int valueFromEnumKey(QString key);
};


#endif // SETTINGSSERVICE_H
