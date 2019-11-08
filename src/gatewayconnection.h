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
    GatewayConnection(const QUrl &url,
                      bool debug = false,
                      QObject *parent = nullptr);

Q_SIGNALS:
    void payloadReady(GatewayPayload payload);

private Q_SLOTS:
    void onConnected();
    void onMessageReceived(QString message);
    void reconnect();

private:
    int ParseInt(QString key, QString message);
    QString ParseEventPayload(QString message);
    QString ParseEventName(QString message);
    GatewayPayload BuildPayload(QString message);
    bool ValidatePayload(GatewayPayload payload);

    QWebSocket socket_;
    QUrl url_;
    bool debug_;
};

#endif // GATEWAYCONNECTION_H
