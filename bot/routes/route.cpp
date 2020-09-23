#include "route.h"


void
Route::buildRequest(const QString &endpoint, const RequestType requestType,
                    const Bucket bucket, const EventContext &context) {
    QString path = QString("%1%2").arg(Route::DISCORD_API_PATH).arg(endpoint);

    _bucket = bucket;

    _payload = SerializationUtils::toQByteArray(context.getTargetPayload());

    _request = QNetworkRequest(QUrl(path));

    _request.setRawHeader("User-Agent", "QtBot 1.0");

    _request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");

    _requestType = requestType;
}
