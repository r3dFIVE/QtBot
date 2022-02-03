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

#ifndef RESUME_H
#define RESUME_H

#include "jsonserializable.h"


class Resume : public JsonSerializable
{   
    Q_OBJECT

public:
    static const QString TOKEN;
    static const QString SESSION_ID;
    static const QString SEQ;

    Resume(QObject *parent = nullptr) : JsonSerializable(parent) {}
    Resume(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Resume(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Resume(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getSeq()const;
    QJsonValue getSessionId() const;
    QJsonValue getToken() const;
    void setSeq(const QJsonValue &seq);
    void setSessionId(const QJsonValue &sessionId);
    void setToken(const QJsonValue &token);

    Q_PROPERTY(QJsonValue token READ getToken WRITE setToken)
    Q_PROPERTY(QJsonValue session_id READ getSessionId WRITE setSessionId)
    Q_PROPERTY(QJsonValue seq READ getSeq WRITE setSeq)
};

Q_DECLARE_METATYPE(Resume)

#endif // RESUME_H
