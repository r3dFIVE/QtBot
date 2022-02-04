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

#ifndef PRESENCE_H
#define PRESENCE_H

#include "jsonserializable.h"


class UpdateStatus : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString AFK;
    static const QString GAME;
    static const QString SINCE;
    static const QString STATUS;

    UpdateStatus(QObject *parent = nullptr) : JsonSerializable(parent) {}
    UpdateStatus(const UpdateStatus &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    UpdateStatus(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    UpdateStatus(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    UpdateStatus(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonObject getGame() const;
    QJsonValue getAfk() const;
    QJsonValue getSince() const;
    QJsonValue getStatus() const;
    void setAfk(const QJsonValue &afk);
    void setGame(const QJsonObject &game);
    void setStatus(const QJsonValue &status);
    void setSince(const QJsonValue &since);

    Q_PROPERTY(QJsonValue since READ getSince WRITE setSince)
    Q_PROPERTY(QJsonObject game READ getGame WRITE setGame)
    Q_PROPERTY(QJsonValue status READ getStatus WRITE setStatus)
    Q_PROPERTY(QJsonValue afk READ getAfk WRITE setAfk)
};

Q_DECLARE_METATYPE(UpdateStatus)

#endif // PRESENCE_H
