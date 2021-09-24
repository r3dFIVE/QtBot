#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>

#include "payloads/jsonserializable.h"

class HttpResponse : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QJsonArray object READ object CONSTANT)

    QString _contentType;
    QString _responseText;
    int _statusCode = 0;

public:    
    explicit HttpResponse(QObject *parent = nullptr) : QObject(parent) {}
    HttpResponse(const HttpResponse &other);
    ~HttpResponse() {
        qDebug() << "!!!!!!!!!!!!DELETED HTTPRESPONSE!!!!!!!!!!";
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

//Q_DECLARE_METATYPE(HttpResponse)

#endif // HTTPRESPONSE_H
