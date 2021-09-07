#include "file.h"
#include "http.h"
#include "httpmultipart.h"
#include "httpresponse.h"

#include "util/httputils.h"
#include "util/mimeutils.h"
#include "util/serializationutils.h"


Http::Http() {
    _botAuthHeaderName = QString("Authorization").toUtf8();

    _botAuthHeaderValue = QString("Bot %1").arg(HttpUtils::botToken()).toUtf8();
}

Http::Http(const Http &other) {
    if (this == &other) {
        return;
    }

    _enableBotAuth = other._enableBotAuth;

    _rawHeaders = other._rawHeaders;

    _downloadDirectory = other._downloadDirectory;

    _filePrefix = other._filePrefix;

    _botAuthHeaderName = other._botAuthHeaderName;

    _botAuthHeaderValue = other._botAuthHeaderValue;
}

Http&
Http::operator=(const Http &other) {
    if (this == &other) {
        return *this;
    }

    _enableBotAuth = other._enableBotAuth;

    _rawHeaders = other._rawHeaders;

    _downloadDirectory = other._downloadDirectory;

    _filePrefix = other._filePrefix;

    _botAuthHeaderName = other._botAuthHeaderName;

    _botAuthHeaderValue = other._botAuthHeaderValue;

    return *this;
}

QJsonObject
Http::processReply(QSharedPointer<QNetworkReply> reply) {
    HttpUtils::waitForReply(reply);

    HttpResponse response;

    if (reply->error()) {
        response.statusCode(reply->error());

        QString failureMessage = QString("QNetworkReply error code: %1. Reason: %2")
                .arg(reply->error())
                .arg(reply->errorString());

        response.content(failureMessage);

        _logger->warning(failureMessage);

        return response.toQJsonObject();
    }

    QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);

    if (contentType.isValid()) {
        response.contentType(contentType.value<QString>());
    }

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (statusCode.isValid()) {
        response.statusCode(statusCode.value<int>());
    }


    if (MimeUtils::isTextContent(response.contentType())) {
        response.content(reply->readAll());

    } else {
        writeToFile(reply, response);
    }

    return response.toQJsonObject();
}

void
Http::writeToFile(QSharedPointer<QNetworkReply> reply, HttpResponse &response) {
    QString targetName = QString("%1/%2%3")
            .arg(_downloadDirectory.path())
            .arg(_filePrefix)
            .arg(reply->url().fileName());

    if (!_downloadDirectory.exists()) {
        if (!_downloadDirectory.mkpath(".")) {
            _logger->warning(QString("Failed to create path: %1.").arg(_downloadDirectory.path()));
        }
    }

    QFile file(targetName);

    if (file.open(QFile::WriteOnly)) {
        response.content(targetName);

        file.write(reply->readAll());

    } else {
        QString failureMessage = QString("Failed to open file for writing: %1. Reason: %2")
                .arg(targetName)
                .arg(file.errorString());

        response.content(failureMessage);

        _logger->warning(failureMessage);
    }
}

void
Http::addHeadersToRequest(QNetworkRequest &request) {
    if (_enableBotAuth) {
        request.setRawHeader(_botAuthHeaderName, _botAuthHeaderValue);
    }

    QMapIterator<QString, QString> headers(_rawHeaders);
    while (headers.hasNext()) {
        request.setRawHeader(headers.key().toUtf8(), headers.value().toUtf8());
    }
}

QJsonObject
Http::get(const QString &url) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addHeadersToRequest(request);

    QNetworkReply *rawReply = manager.get(request);

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

QJsonObject
Http::post(const QString &url, const QJsonObject &json) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addHeadersToRequest(request);

    QNetworkReply *rawReply = manager.post(request, SerializationUtils::toQByteArray(json));

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

QJsonObject
Http::post(const QString &url, QVariant formMultiPart) {
    QJsonObject json;

    if (formMultiPart.isValid() && HttpMultiPart::TYPE_NAME == formMultiPart.typeName()) {
        QNetworkAccessManager manager(this);

        QNetworkRequest request(url);

        addHeadersToRequest(request);

        QNetworkReply *rawReply = manager.post(request, SerializationUtils::toQByteArray(json));

        json = processReply(QSharedPointer<QNetworkReply>(rawReply));

    } else {
       json = multiPartFailure();
    }

    return json;
}

QJsonObject
Http::put(const QString &url, const QJsonObject &json) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addHeadersToRequest(request);

    QNetworkReply *rawReply = manager.post(request, SerializationUtils::toQByteArray(json));

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

QJsonObject
Http::put(const QString &url, QVariant formMultiPart) {
    QJsonObject json;

    if (formMultiPart.isValid() && HttpMultiPart::TYPE_NAME == formMultiPart.typeName()) {
        QNetworkAccessManager manager(this);

        QNetworkRequest request(url);

        addHeadersToRequest(request);

        QNetworkReply *rawReply = manager.put(request, SerializationUtils::toQByteArray(json));

        json = processReply(QSharedPointer<QNetworkReply>(rawReply));

    } else {
       json = multiPartFailure();
    }

    return json;
}

QJsonObject
Http::patch(const QString &url, const QJsonObject &json) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addHeadersToRequest(request);

    QNetworkReply *rawReply = manager.post(request, SerializationUtils::toQByteArray(json));

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

QJsonObject
Http::patch(const QString &url, QVariant formMultiPart) {
    QJsonObject json;

    if (formMultiPart.isValid() && HttpMultiPart::TYPE_NAME == formMultiPart.typeName()) {
        QNetworkAccessManager manager(this);

        QNetworkRequest request(url);

        addHeadersToRequest(request);

        QNetworkReply *rawReply = manager.put(request, SerializationUtils::toQByteArray(json));

        json = processReply(QSharedPointer<QNetworkReply>(rawReply));

    } else {
       json = multiPartFailure();
    }

    return json;
}

QJsonObject
Http::del(const QString &url) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addHeadersToRequest(request);

    QNetworkReply *rawReply = manager.deleteResource(request);

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

void
Http::enableBotAuth(const bool enable) {
    _enableBotAuth = enable;
}


void
Http::addRawHeader(const QString &headerName, const QString &headerValue) {
    _rawHeaders[headerName] = headerValue;
}

void Http::clearRawHeaders() {
    _rawHeaders.clear();
}

QString
Http::downloadDirectory() {
    return _downloadDirectory.path();
}

void
Http::downloadDirectory(const QString &dir) {
    _downloadDirectory = QDir(dir);
}

QString
Http::filePrefix() {
    return _filePrefix;
}

void
Http::filePrefix(const QString &prefix) {
    _filePrefix = prefix + "_";
}

QJsonObject
Http::multiPartFailure() {
    HttpResponse response;

    QString failureMessage("Must pass in a valid FormMultiPart for given POST operation.");

    response.statusCode(BAD_REQUEST);

    response.content(failureMessage);

    _logger->warning(failureMessage);

    return response.toQJsonObject();
}





