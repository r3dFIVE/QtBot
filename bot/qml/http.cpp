#include "http.h"

#include "file.h"
#include "util/httputils.h"
#include "util/mimeutils.h"
#include "util/serializationutils.h"


Http::Http(QObject *parent) : QObject(parent) {
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

HttpResponse*
Http::processReply(QSharedPointer<QNetworkReply> reply, QVariant fileVar)  {
    HttpUtils::waitForReply(reply);

    HttpResponse *response = new HttpResponse(this);

    if (reply->error()) {
        response->statusCode(reply->error());

        QString failureMessage = QString("QNetworkReply error code: %1. Reason: %2")
                .arg(reply->error())
                .arg(reply->errorString());

        response->text(failureMessage);

        _logger->warning(failureMessage);

        return response;
    }

    QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);

    if (contentType.isValid()) {
        response->contentType(contentType.value<QString>());
    }

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (statusCode.isValid()) {
        response->statusCode(statusCode.value<int>());
    }


    if (MimeUtils::isTextContent(response->contentType())) {
        response->text(reply->readAll());

    } else {
        writeToFile(reply, response, fileVar);
    }

    return response;
}

void
Http::writeToFile(QSharedPointer<QNetworkReply> reply, HttpResponse *response, QVariant fileVar) {
    if (fileVar.isValid()) {
        File *file = fileVar.value<File*>();

        write(reply->readAll(), response, file->get());

        return;

    } else {
        _logger->warning("Must pass a valid existing File. Using default download directory and filename.");
    }

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

    write(reply->readAll(), response, &file);
}

void
Http::write(const QByteArray data, HttpResponse *response, QFile *file) {
    if (!file->isOpen()) {
        if (!file->open(QFile::WriteOnly)) {
            QString failureMessage = QString("Failed to open file for writing: %1. Reason: %2")
                    .arg(file->fileName())
                    .arg(file->errorString());

            response->text(failureMessage);

            _logger->warning(failureMessage);

            return;
        }
    }

    response->text(file->fileName());

    file->write(data);    
}

void
Http::addCommonHeadersToRequest(QNetworkRequest &request, bool isJsonPayload) {
    if (_enableBotAuth) {
        request.setRawHeader(_botAuthHeaderName, _botAuthHeaderValue);

        request.setRawHeader("User-Agent", "QtBot 1.0");
    }

    if (isJsonPayload) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/formdata");
    }

    QMapIterator<QString, QString> headers(_rawHeaders);
    while (headers.hasNext()) {
        headers.next();

        request.setRawHeader(headers.key().toUtf8(), headers.value().toUtf8());
    }
}

HttpResponse*
Http::get(const QString &url, QVariant fileVar) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addCommonHeadersToRequest(request);

    QNetworkReply *rawReply = manager.get(request);

    return processReply(QSharedPointer<QNetworkReply>(rawReply), fileVar);
}

HttpResponse*
Http::post(const QString &url, const QJsonObject &json, QVariant fileVar) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addCommonHeadersToRequest(request);

    QNetworkReply *rawReply = manager.post(request, SerializationUtils::toQByteArray(json));

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

HttpResponse*
Http::post(const QString &url, HttpMultiPart *formMultiPart, QVariant fileVar) {
    HttpResponse *response = new HttpResponse(this);

    if (formMultiPart) {
        QNetworkAccessManager manager(this);

        QNetworkRequest request(url);

        addCommonHeadersToRequest(request, false);

        QNetworkReply *rawReply = manager.post(request, formMultiPart->get());

        response = processReply(QSharedPointer<QNetworkReply>(rawReply));

    } else {
       response = multiPartFailure();
    }

    return response;
}

HttpResponse*
Http::put(const QString &url, const QJsonObject &json, QVariant fileVar) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addCommonHeadersToRequest(request);

    QNetworkReply *rawReply = manager.post(request, SerializationUtils::toQByteArray(json));

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

HttpResponse*
Http::put(const QString &url, HttpMultiPart *formMultiPart, QVariant fileVar) {
    HttpResponse *response = new HttpResponse(this);

    if (formMultiPart) {
        QNetworkAccessManager manager(this);

        QNetworkRequest request(url);

        addCommonHeadersToRequest(request, false);

        QNetworkReply *rawReply = manager.put(request, formMultiPart->get());

        response = processReply(QSharedPointer<QNetworkReply>(rawReply));

    } else {
       response = multiPartFailure();
    }

    return response;
}

HttpResponse*
Http::patch(const QString &url, const QJsonObject &json, QVariant fileVar) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addCommonHeadersToRequest(request);

    QNetworkReply *rawReply = manager.post(request, SerializationUtils::toQByteArray(json));

    return processReply(QSharedPointer<QNetworkReply>(rawReply));
}

HttpResponse*
Http::patch(const QString &url, HttpMultiPart *formMultiPart, QVariant fileVar) {
    HttpResponse *response = new HttpResponse(this);

    if (formMultiPart) {
        QNetworkAccessManager manager(this);

        QNetworkRequest request(url);

        addCommonHeadersToRequest(request, false);

        QNetworkReply *rawReply = manager.put(request, formMultiPart->get());

        response = processReply(QSharedPointer<QNetworkReply>(rawReply), fileVar);

    } else {
       response = multiPartFailure();
    }

    return response;
}

HttpResponse*
Http::del(const QString &url) {
    QNetworkAccessManager manager(this);

    QNetworkRequest request(url);

    addCommonHeadersToRequest(request);

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

HttpResponse*
Http::multiPartFailure()  {
    HttpResponse *response = new HttpResponse(this);

    QString failureMessage("Must pass in a valid FormMultiPart for given POST operation.");

    response->statusCode(BAD_REQUEST);

    response->text(failureMessage);

    _logger->warning(failureMessage);

    return response;
}





