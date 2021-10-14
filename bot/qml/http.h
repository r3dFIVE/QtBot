#ifndef HTTP_H
#define HTTP_H

#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QMimeType>
#include <QNetworkAccessManager>

#include "httpresponse.h"
#include "logging/logfactory.h"
#include "file.h"
#include "httpmultipart.h"


class Http : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    const int BAD_REQUEST = 400;

    bool _enableBotAuth = false;
    bool _ignoreSslErrors = false;
    QMap<QString, QString> _rawHeaders;
    QDir _downloadDirectory = QDir(QString("downloads"));
    QString _filePrefix;

    void addCommonHeadersToRequest(QNetworkRequest &request, bool isJsonPayload = true);
    HttpResponse* processReply(QSharedPointer<QNetworkReply> reply, QVariant fileVar = QVariant());
    void writeToFile(QSharedPointer<QNetworkReply> reply, HttpResponse *reponse, QVariant fileVar = QVariant());
    void write(const QByteArray data, HttpResponse *response, QFile *file);
    HttpResponse* multiPartFailure();

    QByteArray _botAuthHeaderName;
    QByteArray _botAuthHeaderValue;

public:
    Http(QObject *parent = nullptr);
    Http(const Http &other, QObject *parent = nullptr);
    ~Http() {}

    Q_INVOKABLE Http &operator=(const Http &other);

    Q_INVOKABLE HttpResponse* get(const QString &url, QVariant fileVariant = QVariant());
    Q_INVOKABLE HttpResponse* post(const QString &path, const QJsonObject &json, QVariant fileVariant = QVariant());
    Q_INVOKABLE HttpResponse* post(const QString &path, HttpMultiPart *formMultiPart, QVariant fileVariant = QVariant());
    Q_INVOKABLE HttpResponse* put(const QString &path, const QJsonObject &json, QVariant fileVariant = QVariant());
    Q_INVOKABLE HttpResponse* put(const QString &path, HttpMultiPart *formMultiPart, QVariant fileVariant = QVariant());
    Q_INVOKABLE HttpResponse* patch(const QString &path, const QJsonObject &json, QVariant fileVariant = QVariant());
    Q_INVOKABLE HttpResponse* patch(const QString &path, HttpMultiPart *formMultiPart, QVariant fileVariant = QVariant());
    Q_INVOKABLE HttpResponse* del(const QString &url);

    Q_INVOKABLE void enableBotAuth(const bool enable);
    Q_INVOKABLE void addRawHeader(const QString &headerName, const QString &headerValue);
    Q_INVOKABLE void clearRawHeaders();
    Q_INVOKABLE QString downloadDirectory();
    Q_INVOKABLE void downloadDirectory(const QString &dir);
    Q_INVOKABLE QString filePrefix();
    Q_INVOKABLE void filePrefix(const QString &prefix);
    Q_INVOKABLE void ignoreSslErrors(const bool ignore);
    Q_INVOKABLE bool ignoreSslErrors();
};

Q_DECLARE_METATYPE(Http)

#endif // HTTP_H
