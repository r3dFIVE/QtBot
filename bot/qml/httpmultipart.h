#ifndef HTTPMULTIPART_H
#define HTTPMULTIPART_H

#include <QHttpMultiPart>
#include <QObject>
#include <QSharedPointer>

#include "logging/logfactory.h"

#include "httppart.h"


class HttpMultiPart : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    QSharedPointer<QHttpMultiPart> _httpMultiPart;

public:
    HttpMultiPart();
    HttpMultiPart(const HttpMultiPart &other);
    ~HttpMultiPart() {}

    Q_INVOKABLE HttpMultiPart &operator=(const HttpMultiPart &other);

    Q_INVOKABLE void append(HttpPart *httpPart);

    QHttpMultiPart* get();
};

Q_DECLARE_METATYPE(HttpMultiPart)

#endif // HTTPMULTIPART_H
