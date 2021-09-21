#include "httpresponse.h"


HttpResponse::HttpResponse(const HttpResponse &other)  {
    if (this == &other) {
        return;
    }

    _responseText = other._responseText;

    _contentType = other._contentType;

    _statusCode = other._statusCode;
}

HttpResponse&
HttpResponse::operator=(const HttpResponse &other)  {
    if (this == &other) {
        return *this;
    }

    _responseText = other._responseText;

    _contentType = other._contentType;

    _statusCode = other._statusCode;

    return *this;
}

QString
HttpResponse::text() const {
    return _responseText;
}

void
HttpResponse::text(const QString &text) {
    _responseText = text;
}

QString
HttpResponse::contentType() const {
    return _contentType;
}

void
HttpResponse::contentType(const QString &contentType) {
    _contentType = contentType;
}

QJsonArray
HttpResponse::object() {
    QJsonArray array;

    QJsonDocument doc = QJsonDocument::fromJson(_responseText.toUtf8());

    if (doc.isEmpty() || doc.isNull()) {
        return array;
    }

    if (doc.isArray()) {
        array = doc.array();
    } else {
        array << doc.object();
    }

    return array;
}

int
HttpResponse::statusCode() const {
    return _statusCode;
}

void
HttpResponse::statusCode(int statusCode) {
    _statusCode = statusCode;
}
