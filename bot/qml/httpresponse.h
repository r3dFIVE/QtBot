#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>

#include "payloads/jsonserializable.h"

class HttpResponse : public JsonSerializable
{
    Q_OBJECT

    static const QString CONTENT_TYPE;
    static const QString STATUS_CODE;
    static const QString CONTENT;

public:
    static const QString TYPE_NAME;

    QString content() const;
    void content(const QString &content);
    QString contentType() const;
    void contentType(const QString &contentType);
    int statusCode() const;
    void statusCode(const int statusCode);

};

#endif // HTTPRESPONSE_H
