#ifndef GUILDENTITY_H
#define GUILDENTITY_H

#include <QObject>
#include <QMap>

#include "botjob/commandbinding.h"
#include "botjob/job.h"
#include "payloads/eventcontext.h"


class GuildEntity : public QObject
{
    Q_OBJECT

    QMap<QString, CommandBinding> _commandBindings;
    QMap<QString, QStringList> _mappedIdsByCommand;
    QString _id;

    bool canInvoke(QString command, QStringList ids);

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

    Job* getBotJob(QSharedPointer<EventContext> context);

    QString id() const;
    void setId(const QString &id);
    void setCommandBindings(const QList<CommandBinding> &commandBindings);

private:
    RestrictionScheme _scheme;

signals:

};

#endif // GUILDENTITY_H
