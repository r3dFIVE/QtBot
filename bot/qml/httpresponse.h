#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>

#include "logging/logfactory.h"

class HttpResponse : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QJsonArray object READ object CONSTANT)

    Logger *_logger = LogFactory::getLogger();
    QString _contentType;
    QString _responseText;
    int _statusCode = 0;

public:    
    explicit HttpResponse(QObject *parent = nullptr) : QObject(parent) {}
    HttpResponse(const HttpResponse &other, QObject *parent = nullptr);
    ~HttpResponse() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed HttpResponse(%1)").arg(ptrStr));
    }

    Q_INVOKABLE HttpResponse &operator=(const HttpResponse &other);

    Q_INVOKABLE QString text() const;
    void text(const QString &content);
    Q_INVOKABLE QString contentType() const;
    void contentType(const QString &contentType);
    Q_INVOKABLE int statusCode() const;
    void statusCode(const int statusCode);
    Q_INVOKABLE QJsonArray object();
};

Q_DECLARE_METATYPE(HttpResponse*)

#endif // HTTPRESPONSE_H
