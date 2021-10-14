#include "httpmultipart.h"

#include <QDebug>


HttpMultiPart::HttpMultiPart(QObject *parent) : QObject(parent) {
    _httpMultiPart = QSharedPointer<QHttpMultiPart>(new QHttpMultiPart(QHttpMultiPart::FormDataType));
}

HttpMultiPart::HttpMultiPart(const HttpMultiPart &other, QObject *parent) : QObject(parent) {
    if (this == &other) {
        return;
    }

    _httpMultiPart = other._httpMultiPart;
}

HttpMultiPart&
HttpMultiPart::operator=(const HttpMultiPart &other) {
    if (this == &other) {
        return *this;
    }

    _httpMultiPart = other._httpMultiPart;

    return *this;
}

void
HttpMultiPart::append(HttpPart *httpPart) {
    if (httpPart) {
        _httpMultiPart->append(httpPart->get());
    } else {
        _logger->warning("Failed to append HttpPart... Must pass in valid HttpPart.");
    }
}

QHttpMultiPart*
HttpMultiPart::get() {
    return _httpMultiPart.data();
}
