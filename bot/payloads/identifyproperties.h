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

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "jsonserializable.h"


class IdentifyProperties : public JsonSerializable
{    
    QString $os = QSysInfo::productType();
    QString $browser = "QtBot";
    QString $device = "QtBot";

public:
    static const QString OS;
    static const QString BROWSER;
    static const QString DEVICE;

    IdentifyProperties();
    IdentifyProperties(const QByteArray &json) : JsonSerializable(json) {}
    IdentifyProperties(const QJsonObject &json) : JsonSerializable(json) {}
    IdentifyProperties(const QString &json) : JsonSerializable(json) {}

    QJsonValue getOS() const;
    QJsonValue getBrowser() const;
    QJsonValue getDevice() const;
    void setBrowser(const QJsonValue &browser);
    void setDevice(const QJsonValue &device);
    void setOS(const QJsonValue &os);

    Q_PROPERTY(QJsonValue browser READ getBrowser WRITE setBrowser)
    Q_PROPERTY(QJsonValue device READ getDevice WRITE setDevice)
    Q_PROPERTY(QJsonValue os READ getOS WRITE setOS)
};

#endif // PROPERTIES_H
