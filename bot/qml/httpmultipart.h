#ifndef HTTPMULTIPART_H
#define HTTPMULTIPART_H

#include <QHttpMultiPart>
#include <QObject>
#include <QSharedPointer>

#include "logging/logfactory.h"


class HttpMultiPart : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    QSharedPointer<QHttpMultiPart> _httpMultiPart;

public:
    static const QString TYPE_NAME;

    HttpMultiPart();
    HttpMultiPart(const HttpMultiPart &other);
    ~HttpMultiPart() {}

    Q_INVOKABLE HttpMultiPart &operator=(const HttpMultiPart &other);

    Q_INVOKABLE void append(QVariant httpPartVar);

    QSharedPointer<QHttpMultiPart> get();
};

#endif // HTTPMULTIPART_H
