#ifndef GUILDENTITY_H
#define GUILDENTITY_H

#include <QObject>
#include <QMap>

#include "util/icommand.h"
#include "qml/eventcontext.h"

class GuildEntity : public QObject
{
    Q_OBJECT

    QMap<QString, ICommand::CommandMapping> _registry;
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

    void invoke(QSharedPointer<EventContext> context);

    QString id() const;
    void setId(const QString &id);
    void setRegistry(const QMap<QString, QPair<QString, QSharedPointer<ICommand>>> &registry);

private:
    RestrictionScheme _scheme;

signals:

};

#endif // GUILDENTITY_H
