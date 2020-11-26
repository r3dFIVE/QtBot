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

#ifndef CLIENTSTATUS_H
#define CLIENTSTATUS_H

#include "jsonserializable.h"


class ClientStatus : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString DESKTOP;
    static const QString MOBILE;
    static const QString WEB;

    ClientStatus() {}
    ClientStatus(const QByteArray &json) : JsonSerializable(json) {}
    ClientStatus(const QJsonObject &json) : JsonSerializable(json) {}
    ClientStatus(const QString &json) : JsonSerializable(json) {}

    QJsonValue getDesktop() const;
    QJsonValue getMobile() const;
    QJsonValue getWeb() const;
    void setDesktop(const QJsonValue &desktop);
    void setMobile(const QJsonValue &mobile);
    void setWeb(const QJsonValue &web);

    Q_PROPERTY(QJsonValue desktop READ getDesktop WRITE setDesktop)
    Q_PROPERTY(QJsonValue mobile READ getMobile WRITE setMobile)
    Q_PROPERTY(QJsonValue web READ getWeb WRITE setWeb)
};

Q_DECLARE_METATYPE(ClientStatus)

#endif // CLIENTSTATUS_H
