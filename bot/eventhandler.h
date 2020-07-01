#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "util/function.h"
#include "payloads/gatewaypayload.h"
#include "payloads/message.h"
#include "databasedriver.h"
#include "util/settings.h"
#include "logging/logfactory.h"

#include <QObject>
#include <QSqlQuery>


class EventHandler : public QObject
{
    Q_OBJECT

    QSharedPointer<Settings> _settings;

    QSqlQuery _query;
    Logger *_logger;    
    QSharedPointer<DatabaseDriver> _databaseDriver;
    QMap<QString, Function<void(const Message &args)>> _commands;

    QString parseCommandToken(QString message);
    void processDispatch(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void logQuery();

public:
    EventHandler(QSharedPointer<Settings> settings);

public slots:
    void init();
    void processEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload);

};

#endif // MESSAGEHANDLER_H
