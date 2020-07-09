#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "util/corecommand.h"
#include "payloads/gatewaypayload.h"
#include "payloads/message.h"
#include "qml/registrarfactory.h"
#include "util/settings.h"
#include "logging/logfactory.h"

#include <QObject>
#include <QSqlQuery>


class EventHandler : public QObject
{
    Q_OBJECT

    QSharedPointer<CommandRegistrar> _scriptRegistrar;
    QSharedPointer<Settings> _settings;

    QString _botToken;
    QString _scriptDir;
    QSqlQuery _query;
    Logger *_logger;    

    QString parseCommandToken(QString message);
    void processDispatch(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void processMessageCreate(QSharedPointer<GatewayPayload::GatewayPayload> payload);

public:
    EventHandler(QSharedPointer<Settings> settings);

public slots:
    void processEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void processRegistrar(QSharedPointer<CommandRegistrar> registrar);
    void init();
};

#endif // MESSAGEHANDLER_H
