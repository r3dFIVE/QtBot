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
HttpUtils::waitForReply(QSharedPointer<QNetworkReply> reply) {
    QEventLoop loop;

    QObject::connect(reply.data(), SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();
}
