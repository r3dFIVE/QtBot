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

#ifndef ROUTE_H
#define ROUTE_H

#include <QNetworkRequest>
#include <QObject>

#include "payloads/eventcontext.h"
#include "payloads/jsonserializable.h"
#include "payloads/message.h"
#include "util/serializationutils.h"


class Route : public QObject
{
    Q_OBJECT

public:
    static const QString GLOBAL_BUCKET;

    enum RequestType {
        POST,       // C
        GET,        // R
        PUT,        // U (Update/Replace)
        PATCH,      // U (Update/Modify)
        DELETE,     // D
    };
    Q_ENUM(RequestType);

    inline QNetworkRequest request() {
        return _request;
    }

    inline QByteArray payload() {
        return _payload;
    }

    inline void addRawHeader(const QByteArray &headerName, const QByteArray &headerValue) {
        _request.setRawHeader(headerName, headerValue);
    }

    inline RequestType getType() {
        return _requestType;
    }


    inline QString getMajorParamId() {
        return _majorParamId;
    }

    inline QString getRouteWithMethod() {
        return _routeWithMethod;
    }

protected:
    Route() {}
    Route(const Route &other) { Q_UNUSED(other) }
    ~Route() {}

    QMap<QString, QString> _pathParams;
    QByteArray _payload;
    QNetworkRequest _request;
    QString _majorParamId;
    QString _routeWithMethod;
    RequestType _requestType;

    const QString DISCORD_API_PATH = "https://discord.com/api";
    const QString CHANNEL_ID_TOKEN = "{channel.id}";
    const QString GUILD_ID_TOKEN = "{guild.id}";
    const QString INTEGRATION_ID_TOKEN = "{integration.id}";
    const QString INVITE_CODE_TOKEN = "{invite.code}";
    const QString WEBHOOK_ID_TOKEN = "{webhook.id}";
    const QString WEBHOOK_TOKEN_TOKEN = "{webhook.token}";
    const QString MESSAGE_ID_TOKEN = "{message.id}";
    const QString EMOJI_TOKEN = "{emoji}";
    const QString USER_ID_TOKEN = "{user.id}";
    const QString ROLE_ID_TOKEN = "{role.id}";
    const QString OVERWRITE_ID_TOKEN = "{overwrite.id}";

    void buildRequest(const RequestType requestType,
                      const QString &route,
                      const QString &majorParamId,
                      const EventContext &context);

    void buildRequest(const RequestType requestType,
                      const QString &route,
                      const EventContext &context) {
        buildRequest(requestType, route, GLOBAL_BUCKET, context);
    }

    void buildRequest(const RequestType requestType,
                      const QString &route,
                      const QString &majorParamId) {
        buildRequest(requestType, route, majorParamId, EventContext());
    }

    void buildRequest(const RequestType requestType,
                      const QString &route) {
        buildRequest(requestType, route, GLOBAL_BUCKET, EventContext());
    }
};


#endif // ROUTE_H
