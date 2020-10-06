#include "route.h"

void
Route::buildRequest(const RequestType requestType,
                    const QString &route,
                    const QString &majorParamId,
                    const QJsonObject &payload) {
    QString path = QString("%1%2").arg(Route::DISCORD_API_PATH, route);

    for (auto key : _params.keys()) {
        path.replace(key, _params[key]);
    }

    _majorParamId = majorParamId;

    _payload = SerializationUtils::toQByteArray(payload);

    _request = QNetworkRequest(QUrl(path));

    _request.setRawHeader("User-Agent", "QtBot 1.0");

    _request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    _requestType = requestType;

    _routeWithMethod = QString("%1%2").arg(QString::number(_requestType), route);
}
