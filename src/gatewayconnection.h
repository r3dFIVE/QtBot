#ifndef GATEWAYCONNECTION_H
#define GATEWAYCONNECTION_H

#include <QObject>
#include <QQueue>
#include <QtWebSockets/QWebSocket>

#include "payloads/gatewaypayload.h"


class GatewayConnection : public QObject
{
    Q_OBJECT

public:
    GatewayConnection(const QUrl &url, QObject *parent = nullptr);

Q_SIGNALS:
    void payloadReady(GatewayPayload payload);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray message);
    void reconnect();

private:
    QWebSocket socket_;
    QUrl url_;
    bool debug_ = true;
};

#endif // GATEWAYCONNECTION_H
