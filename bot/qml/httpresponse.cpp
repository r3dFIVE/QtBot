#include "httpresponse.h"


const QString HttpResponse::CONTENT_TYPE = "content_type";
const QString HttpResponse::STATUS_CODE = "status_code";
const QString HttpResponse::CONTENT = "content";

QString
HttpResponse::content() const {
    return _jsonObject[CONTENT].toString();
}

void
HttpResponse::content(const QString &content) {
    _jsonObject[CONTENT] = content;
}

QString
HttpResponse::contentType() const {
    return _jsonObject[CONTENT_TYPE].toString();
}

void
HttpResponse::contentType(const QString &contentType) {
    _jsonObject[CONTENT_TYPE] = contentType;
}

int
HttpResponse::statusCode() const {
    return _jsonObject[STATUS_CODE].toInt();
}

void
HttpResponse::statusCode(int statusCode) {
    _jsonObject[STATUS_CODE] = statusCode;
}
