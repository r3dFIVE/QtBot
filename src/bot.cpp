#include "bot.h"
#include "messagehandler.h"

Bot::Bot(QSharedPointer<QSettings> settings) : m_settings(settings)
{
    qRegisterMetaType<QSharedPointer<JsonSerializeable>>();

    qDebug() << QSysInfo::kernelType();
    qDebug() << m_settings->isWritable();
    qDebug() << m_settings->value("test_val").toBool();
    qDebug() << m_settings->value("bot_token").toString();
}

void
Bot::run() {
    QUrl connectionUrl = buildConnectionUrl();
    GatewayConnection *connection = new GatewayConnection(QUrl(QStringLiteral("ws://172.21.98.196:1234")), nullptr);
    connection->moveToThread(&m_gatewayThread);
    connect(&m_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);
    connect(&m_gatewayThread, &QThread::started, connection, &GatewayConnection::init);

    MessageHandler *messageHandler = new MessageHandler;
    messageHandler->moveToThread(&m_messageHandlerThread);
    connect(&m_messageHandlerThread, &QThread::finished, messageHandler, &QObject::deleteLater);
    connect(connection, &GatewayConnection::payloadReady, messageHandler, &MessageHandler::processPayload);

    m_messageHandlerThread.start();
    m_gatewayThread.start();
    m_gatewayThread.setPriority(QThread::HighestPriority);
}

QUrl
Bot::buildConnectionUrl() {
    QUrl url("url");
    return url;
}
