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

    Logger *_logger = LogFactory::getLogger(this);

    QSharedPointer<QHttpMultiPart> _httpMultiPart;

public:
    HttpMultiPart(QObject *parent = nullptr);
    HttpMultiPart(const HttpMultiPart &other, QObject *parent = nullptr);
    ~HttpMultiPart() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed HttpMultiPart(%1)").arg(ptrStr));
    }

    Q_INVOKABLE HttpMultiPart &operator=(const HttpMultiPart &other);

    Q_INVOKABLE void append(HttpPart *httpPart);

    QHttpMultiPart* get();
};

Q_DECLARE_METATYPE(HttpMultiPart)

#endif // HTTPMULTIPART_H
