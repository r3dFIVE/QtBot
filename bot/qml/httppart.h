#ifndef HTTPPART_H
#define HTTPPART_H

#include <QHttpPart>

#include "logging/logfactory.h"
#include "enums/networkrequest.h"
#include "file.h"


class HttpPart : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);

    QHttpPart _httpPart;

public:
    Q_INVOKABLE HttpPart(QObject *parent = nullptr) : QObject(parent) {};
    Q_INVOKABLE HttpPart(const HttpPart &other, QObject *parent = nullptr);
    Q_INVOKABLE ~HttpPart() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed HttpPart(%1)").arg(ptrStr));
    };

    Q_INVOKABLE HttpPart &operator=(const HttpPart &other);

    Q_INVOKABLE void setBody(const QJsonObject &body);
    Q_INVOKABLE void setBody(const QString &body);
    Q_INVOKABLE void setBodyDevice(File *file);
    Q_INVOKABLE void setHeader(int headerNum, const QString &value);
    Q_INVOKABLE void setRawHeader(const QString &headerName, const QString &headerValue);

    QHttpPart get() const;
};

Q_DECLARE_METATYPE(HttpPart)

#endif // HTTPPART_H
