#include "httputils.h"


QString HttpUtils::_botToken = "";

QString
HttpUtils::botToken() {
    return _botToken;
}

void
HttpUtils::setBotToken(const QString &token) {
    _botToken = token;
}

void
HttpUtils::waitForReply(QSharedPointer<QNetworkReply> reply, const bool ignoreSslErrors) {
    QEventLoop loop;

    if (ignoreSslErrors) {
        QObject::connect(reply.data(), SIGNAL(sslErrors(QList<QSslError>)), reply.data(), SLOT(ignoreSslErrors()));
    }

    QObject::connect(reply.data(), SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();
}

void
HttpUtils::ignoreSslErrors() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    reply->ignoreSslErrors();
}
