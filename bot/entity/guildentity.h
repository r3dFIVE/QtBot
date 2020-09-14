#ifndef GUILDENTITY_H
#define GUILDENTITY_H

#include <QObject>
#include <QMap>
#include <QQmlEngine>

#include "botjob/commandbinding.h"
#include "botjob/gatewaybinding.h"
#include "botjob/timedbinding.h"
#include "botjob/job.h"
#include "payloads/eventcontext.h"


class GuildEntity : public QObject
{
    Q_OBJECT

    QList<TimedBinding> _timedBindings;
    QMap<QString, QList<GatewayBinding> > _gatewayBindings;
    QMap<QString, CommandBinding> _commandBindings;
    QMap<QString, QStringList> _mappedSchemeIdsByCommand;
    QString _id;

    bool canInvoke(QString command, QStringList ids);
    Job* getCommandJob(QSharedPointer<EventContext> context);
    QList<Job*> getGatewayEventJobs(QSharedPointer<EventContext> context) const;
    QString parseCommandToken(const QString &content) const;

public:
    // TODO add scheme to options
    enum RestrictionScheme {
        DISABLED,
        ENABLED
    };

    Q_ENUM(RestrictionScheme)

    explicit GuildEntity(QObject *parent = nullptr) : QObject(parent) {
        _scheme = ENABLED;
    };

    QList<Job *> getBotJobs(QSharedPointer<EventContext> context);
    QList<TimedBinding> getTimedBindings() const;
    QString id() const;
    void setId(const QString &id);
    void setCommandBindings(const QList<CommandBinding> &commandBindings);
    void setGatewayBindings(const QList<GatewayBinding> &gatewayBindings);
    void setTimedBindings(const QList<TimedBinding> &timedBindings);

private:
    RestrictionScheme _scheme;

signals:

};

#endif // GUILDENTITY_H
