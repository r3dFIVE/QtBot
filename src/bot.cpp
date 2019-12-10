#include "bot.h"
#include "eventservice.h"
#include "globals.h"

#include <QCoreApplication>
#include <QDir>

const QString ERROR_CANNOT_BE_BLANK = "%1\n\n%2 cannot be blank. . . exiting.\n";

Bot::Bot(QSharedPointer<QSettings> settings) : m_settings(settings)
{
    validateSettings();
    initializeLogging();

    qRegisterMetaType<QSharedPointer<JsonSerializeable>>();

    qDebug() << QSysInfo::kernelType();
    qDebug() << m_settings->isWritable();
    qDebug() << m_settings->value("test_val").toBool();
    qDebug() << m_settings->value("bot_token").toString();
    qDebug() << m_settings->value("invalid_token").isNull();
}

void
Bot::validateSettings() {

    if (!m_settings) {
        qDebug() << "Error initializing settings file. . . exiting.";
        exit(1);
    }

    QString fileName = QString("[%1]").arg(m_settings->fileName());

    if (m_settings->value(Settings::Connection::BOT_TOKEN).isNull()) {
        invalidSetting(fileName, Settings::Connection::BOT_TOKEN);
    }

    if (m_settings->value(Settings::Connection::CONNECTION_URL).isNull()) {
        m_settings->value(Settings::Connection::CONNECTION_URL) = "wss://gateway.discord.gg";
    }

    if (m_settings->value(Settings::Connection::ZLIB_ENABLED).isNull()) {
        m_settings->value(Settings::Connection::ZLIB_ENABLED) = false;
    }

    if (m_settings->value(Settings::Database::DATABASE_TYPE).isNull()) {
        m_settings->value(Settings::Database::DATABASE_TYPE) = Settings::Database::DatabaseTypes::SQLITE;
    }

    QString databaseType = m_settings->value(Settings::Database::DATABASE_TYPE).toString();

    if (databaseType != Settings::Database::DatabaseTypes::SQLITE) {
        if (m_settings->value(Settings::Database::DATABASE_HOST).isNull()) {
            invalidSetting(fileName, databaseType, Settings::Database::DATABASE_HOST);
        }

        if (m_settings->value(Settings::Database::DATABASE_PORT).isNull()) {
            invalidSetting(fileName, databaseType, Settings::Database::DATABASE_PORT);
        }

        if (m_settings->value(Settings::Database::DATABASE_USER).isNull()) {
            invalidSetting(fileName, databaseType, Settings::Database::DATABASE_USER);
        }

        if (m_settings->value(Settings::Database::DATABASE_PASSWORD).isNull()) {
            invalidSetting(fileName, databaseType, Settings::Database::DATABASE_PASSWORD);
        }
    }

    if (m_settings->value(Settings::Logging::CONSOLE_LOG_LEVEL).isNull()) {
        m_settings->value(Settings::Logging::CONSOLE_LOG_LEVEL) = Settings::Logging::Levels::INFO;
    }

    if (m_settings->value(Settings::Logging::FILE_LOG_LEVEL).isNull()) {
        m_settings->value(Settings::Logging::FILE_LOG_LEVEL) = Settings::Logging::Levels::INFO;
    }

    if (m_settings->value(Settings::Logging::LOG_FILE_SIZE).isNull()) {
        m_settings->value(Settings::Logging::LOG_FILE_SIZE) = 1048576;
    }

    if (m_settings->value(Settings::Logging::LOG_FILE_COUNT).isNull()) {
        m_settings->value(Settings::Logging::LOG_FILE_COUNT) = 10;
    }

    if (m_settings->value(Settings::Logging::LOG_FILE_DIRECTORY).isNull()) {
        m_settings->value(Settings::Logging::LOG_FILE_DIRECTORY) = QDir::currentPath() + QDir::separator() + "logs";
    }
}

void
Bot::invalidSetting(QString fileName, QString databaseType, QString propertyName) {
    if (!(databaseType.isEmpty()))
        qDebug() << Settings::DATABASE_TYPE << ": " << databaseType;

    invalidSetting(fileName, propertyName);
}

void
Bot::invalidSetting(QString fileName, QString propertyName) {
    qDebug().noquote() << QString(ERROR_CANNOT_BE_BLANK).arg(fileName, propertyName);
    exit(1);
}

void
Bot::initializeLogging() {

}

void
Bot::run() {
    QUrl connectionUrl = buildConnectionUrl();
    GatewayService *connection = new GatewayService(QUrl(QStringLiteral("ws://127.0.0.1:1234")), nullptr);
    connection->moveToThread(&m_gatewayThread);
    connect(&m_gatewayThread, &QThread::finished, connection, &QObject::deleteLater);
    connect(&m_gatewayThread, &QThread::started, connection, &GatewayService::init);

    EventService *messageHandler = new EventService;
    messageHandler->moveToThread(&m_messageHandlerThread);
    connect(&m_messageHandlerThread, &QThread::finished, messageHandler, &QObject::deleteLater);
    connect(connection, &GatewayService::payloadReady, messageHandler, &EventService::processEvent);

    m_messageHandlerThread.start();
    m_gatewayThread.start();
    m_gatewayThread.setPriority(QThread::HighestPriority);
}

QUrl
Bot::buildConnectionUrl() {
    QUrl url("url");
    return url;
}
