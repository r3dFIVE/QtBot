#include "httppart.h"

#include "file.h"


const QString HttpPart::TYPE_NAME = "HttpPart";

HttpPart::HttpPart(const HttpPart &other) {
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
HttpPart::setBody(const QString &body) {
    _httpPart.setBody(body.toUtf8());
}

void
HttpPart::setBodyDevice(QVariant fileVar) {
    if (fileVar.isValid() && fileVar.typeName() == File::TYPE_NAME) {
        File file = fileVar.value<File>();

        _httpPart.setBodyDevice(file.get().data());
    } else {
        _logger->warning("Failed to set http part body... Must pass in valid File.");
    }
}

void
HttpPart::setHeader(NetworkRequest::KnownHeaders header, const QString &value) {
    _httpPart.setHeader(QNetworkRequest::KnownHeaders(header), QVariant(value));
}

void
HttpPart::setRawHeader(const QString &headerName, const QString &headerValue) {
    _httpPart.setRawHeader(headerName.toUtf8(), headerValue.toUtf8());
}

QHttpPart
HttpPart::get() const {
    return _httpPart;
}


