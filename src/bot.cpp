#include "bot.h"
#include "eventservice.h"
#include "globals.h"
#include "loggingservice.h"

#include <QDir>
#include <QMetaEnum>


Bot::Bot(QString path)
{   
    _settings = QSharedPointer<SettingsService>(new SettingsService(path));

    LoggingService::initializeLogging(_settings);
    _logger = LoggingService::getLogger();

    _logger->info("QtBot is now starting. . .");

//    qDebug() << QSysInfo::kernelType();
//    qDebug() << _settings->isWritable();
//    qDebug() << _settings->value("test_val").toBool();
//    qDebug() << _settings->value("bot_token").toString();
//    qDebug() << _settings->value("invalid_token").isNull();

    qRegisterMetaType<QSharedPointer<JsonSerializeable>>();
}

void
Bot::run() {
    GatewayService *connection = new GatewayService(_settings);
    connection->moveToThread(&_gatewayThread);
    connect(&_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);
    connect(&_gatewayThread, &QThread::started, connection, &GatewayService::init);

    EventService *messageHandler = new EventService;
    messageHandler->moveToThread(&_messageServiceThread);
    connect(&_messageServiceThread, &QThread::finished, messageHandler, &QObject::deleteLater);
    connect(connection, &GatewayService::eventReady, messageHandler, &EventService::processEvent);

    _messageServiceThread.start();
    _gatewayThread.start();
    _gatewayThread.setPriority(QThread::HighestPriority);
}
