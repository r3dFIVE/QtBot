#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QSettings>
#include <QThread>
#include "gatewayservice.h"

class Bot : public QObject
{
    Q_OBJECT

public:
    Bot(QSharedPointer<QSettings> settings);
    void run();

private:
    QThread m_gatewayThread;
    QThread m_messageHandlerThread;
    QSharedPointer<QSettings> m_settings;

    QUrl buildConnectionUrl();
    void validateSettings();
    void initializeLogging();
    void invalidSetting [[ noreturn ]] (QString fileName, QString propertyName);
    void invalidSetting [[ noreturn ]] (QString fileName, QString databaseType, QString propertyName);
};

#endif // BOT_H
