#ifndef COMMANDRESTRICTIONS_H
#define COMMANDRESTRICTIONS_H

#include <QObject>
#include <QMap>

class CommandRestrictions : public QObject
{
    Q_OBJECT

public:

    enum RestrictionState {
        DISABLED = 0,
        ENABLED = 1
    };
    Q_ENUM(RestrictionState)

    CommandRestrictions(const QString &guildId,
                        const QString &targetId,
                        const QMap<QString, RestrictionState> &restrictions)
        : _guildId(guildId), _targetId(targetId), _restrictions(restrictions) {}

    inline QString getGuildId() const {
        return _guildId;
    }

    inline QString getTargetId() const {
        return _targetId;
    }

    inline QMap<QString, RestrictionState> getRestrictions() const {
        return _restrictions;
    }

private:
    QString _guildId;
    QString _targetId;
    QMap<QString, RestrictionState> _restrictions;
};

#endif // COMMANDRESTRICTIONS_H
