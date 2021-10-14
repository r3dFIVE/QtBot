#include "httppart.h"

#include "util/serializationutils.h"

HttpPart::HttpPart(const HttpPart &other, QObject *parent) : QObject(parent){
    if (this == &other) {
        return;
    }

    _httpPart = other._httpPart;
}

HttpPart&
HttpPart::operator=(const HttpPart &other) {
    if (this == &other) {
        return *this;
    }

    _httpPart = other._httpPart;

    return *this;
}

void
HttpPart::setBody(const QJsonObject &body) {
    _httpPart.setBody(SerializationUtils::toQByteArray(body));
}

void
HttpPart::setBody(const QString &body) {
    _httpPart.setBody(body.toUtf8());
}

void
HttpPart::setBodyDevice(File *file) {
    if (file) {
        _httpPart.setBodyDevice(file->get());
    } else {
        _logger->warning("Failed to set http part body device... Must pass in valid File.");
    }
}

void
HttpPart::setHeader(int headerNum, const QString &value) {
     _httpPart.setHeader(QNetworkRequest::KnownHeaders(headerNum), value);
}

void
HttpPart::setRawHeader(const QString &headerName, const QString &headerValue) {
    _httpPart.setRawHeader(headerName.toUtf8(), headerValue.toUtf8());
}

QHttpPart
HttpPart::get() const {
    return _httpPart;
}


