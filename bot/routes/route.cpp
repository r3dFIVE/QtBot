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

#include "route.h"

const QString Route::GLOBAL_BUCKET = "GLOBAL_BUCKET";

void
Route::buildRequest(const RequestType requestType,
                    const QString &route,
                    const QString &majorParamId,
                    const EventContext &context) {
    QString path = QString("%1%2").arg(Route::DISCORD_API_PATH, route);

    for (auto key : _pathParams.keys()) {
        path.replace(key, _pathParams[key]);
    }

    if (requestType == GET || requestType == POST) {
        if (!context.getQueryParams().isEmpty()) {
            QJsonObject queryParams = context.getQueryParams();

            QString queryString = "?";

            for (auto key : queryParams.keys()) {
                queryString += QString("%1=%2&").arg(key, queryParams[key].toString());
            }

            queryString.truncate(queryString.size() - 1);

            path = QString("%1%2").arg(path, queryString);
        }
    }

    _majorParamId = majorParamId;

    _payload = SerializationUtils::toQByteArray(context.getTargetPayload());

    _request = QNetworkRequest(QUrl(path));

    _request.setRawHeader("User-Agent", "QtBot 1.0");

    _request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    _requestType = requestType;

    _routeWithMethod = QString("%1%2").arg(QString::number(_requestType), route);
}
