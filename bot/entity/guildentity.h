#ifndef GUILDENTITY_H
#define GUILDENTITY_H

#include <QObject>
#include <QMap>

#include "botjob/job.h"
#include "qml/eventcontext.h"

class GuildEntity : public QObject
{
    Q_OBJECT

    QMap<QString, IBotJob::CommandMapping> _registry;
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
    void setRegistry(const QMap<QString, QPair<QString, QSharedPointer<IBotJob>>> &registry);

private:
    RestrictionScheme _scheme;

signals:

};

#endif // GUILDENTITY_H
