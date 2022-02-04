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

#ifndef SECRETS_H
#define SECRETS_H

#include "jsonserializable.h"


class ActivitySecrets : public JsonSerializable
{
    Q_OBJECT

public:    
    static const QString JOIN;
    static const QString MATCH;
    static const QString SPECTATE;

    ActivitySecrets(QObject *parent = nullptr) : JsonSerializable(parent) {}
    ActivitySecrets(const ActivitySecrets &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    ActivitySecrets(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    ActivitySecrets(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    ActivitySecrets(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getJoin() const;
    QJsonValue getMatch() const;
    QJsonValue getSpectate() const;
    void setJoin(const QJsonValue &join);
    void setMatch(const QJsonValue &match);
    void setSpectate(const QJsonValue &spectate);

    Q_PROPERTY(QJsonValue join READ getJoin WRITE setJoin)
    Q_PROPERTY(QJsonValue spectate READ getSpectate WRITE setSpectate)
    Q_PROPERTY(QJsonValue match READ getMatch WRITE setMatch)
};

Q_DECLARE_METATYPE(ActivitySecrets)

#endif // SECRETS_H
