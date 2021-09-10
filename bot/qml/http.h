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
    QMap<QString, QString> _rawHeaders;
    QDir _downloadDirectory = QDir(QString("downloads"));
    QString _filePrefix;

    void addCommonHeadersToRequest(QNetworkRequest &request, bool isJsonPayload = true);
    QJsonObject processReply(QSharedPointer<QNetworkReply> reply);
    void writeToFile(QSharedPointer<QNetworkReply> reply, HttpResponse &reponse);
    QJsonObject multiPartFailure();

    QByteArray _botAuthHeaderName;
    QByteArray _botAuthHeaderValue;

public:
    Http();
    Http(const Http &other);
    ~Http() {}

    Q_INVOKABLE Http &operator=(const Http &other);

    Q_INVOKABLE QJsonObject get(const QString &url);
    Q_INVOKABLE QJsonObject post(const QString &path, const QJsonObject &json);
    Q_INVOKABLE QJsonObject post(const QString &path, HttpMultiPart *formMultiPart);
    Q_INVOKABLE QJsonObject put(const QString &path, const QJsonObject &json);
    Q_INVOKABLE QJsonObject put(const QString &path, HttpMultiPart *formMultiPart);
    Q_INVOKABLE QJsonObject patch(const QString &path, const QJsonObject &json);
    Q_INVOKABLE QJsonObject patch(const QString &path, HttpMultiPart *formMultiPart);
    Q_INVOKABLE QJsonObject del(const QString &url);

    Q_INVOKABLE void enableBotAuth(const bool enable);
    Q_INVOKABLE void addRawHeader(const QString &headerName, const QString &headerValue);
    Q_INVOKABLE void clearRawHeaders();
    Q_INVOKABLE QString downloadDirectory();
    Q_INVOKABLE void downloadDirectory(const QString &dir);
    Q_INVOKABLE QString filePrefix();
    Q_INVOKABLE void filePrefix(const QString &prefix);
};

Q_DECLARE_METATYPE(Http)

#endif // HTTP_H
