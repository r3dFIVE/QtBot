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

#ifndef RATELIMIT_H
#define RATELIMIT_H

#include <QObject>

#include "jsonserializable.h"


class RateLimit : public JsonSerializable
{
public:
    static const QString GLOBAL;
    static const QString MESSAGE;
    static const QString RETRY_AFTER;

    RateLimit() {}
    RateLimit(const QByteArray &json) : JsonSerializable(json) {}
    RateLimit(const QJsonObject &json) : JsonSerializable(json) {}
    RateLimit(const QString &json) : JsonSerializable(json) {}

    QJsonValue getGlobal() const;
    QJsonValue getMessage() const;
    QJsonValue getRetryAfter() const;
    void setGlobal(const QJsonValue &global);
    void setMessage(const QJsonValue &message);
    void setRetryAfter(const QJsonValue &retryAfer);

    Q_PROPERTY(QJsonValue global READ getGlobal WRITE getGlobal)
    Q_PROPERTY(QJsonValue message READ getMessage WRITE getMessage)
    Q_PROPERTY(QJsonValue retry_After READ getRetryAfter WRITE getRetryAfter)
};

#endif // RATELIMIT_H
