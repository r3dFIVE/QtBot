#include "httpmultipart.h"
#include "httppart.h"


const QString HttpMultiPart::TYPE_NAME = "HttpMultiPart";

HttpMultiPart::HttpMultiPart() {
    _httpMultiPart = QSharedPointer<QHttpMultiPart>(new QHttpMultiPart(QHttpMultiPart::FormDataType));
}

HttpMultiPart::HttpMultiPart(const HttpMultiPart &other) {
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
HttpMultiPart::append(QVariant httpPartVar) {
    if (httpPartVar.isValid() && HttpPart::TYPE_NAME == httpPartVar.typeName()) {
        HttpPart httpPart = httpPartVar.value<HttpPart>();

        _httpMultiPart->append(httpPart.get());
    } else {
        _logger->warning("Failed to set http part body... Must pass in valid File.");
    }
}

QSharedPointer<QHttpMultiPart>
HttpMultiPart::get() {
    return _httpMultiPart;
}
