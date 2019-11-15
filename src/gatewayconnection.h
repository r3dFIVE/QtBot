#ifndef GATEWAYCONNECTION_H
#define GATEWAYCONNECTION_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

#include "payloads/gatewaypayload.h"


class GatewayConnection : public QObject
{
    Q_OBJECT

public:
    GatewayConnection(const QUrl &url, QObject *parent = nullptr);
    ~GatewayConnection();

public slots:
    void init();
    void sendTextMessage(const JsonSerializeable &message);
    void sendBinaryMessage(const JsonSerializeable &message);
    void updateHeartbeatInterval(int milliseconds);

Q_SIGNALS:
    void payloadReady(int payload);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray message);
    void reconnect();

private:
    QWebSocket *_socket;
    QUrl _url;
    bool _debug = true;
    int _heartbeatInterval;
};

#endif // GATEWAYCONNECTION_H
