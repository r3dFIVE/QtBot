#ifndef USERHELP_H
#define USERHELP_H

#include <QObject>

#include "botscript.h"
#include "ibinding.h"
#include "payloads/embed.h"


class UserHelp : public QObject
{
    Q_OBJECT

    static const QString COMMA_SPACE;

    Logger *_logger = LogFactory::getLogger(this);

    QMap<QString, QList<Embed>> _pages;
    QString _userId;
    QString _channelId;
    QString _guildId;

    Embed buildBindingPage(const QString &name, const QString &description, int pageNum, int total);
    QStringList splitDescription(const QString &description);

    void addMainPages(const QMap<BotScript*, QList<QSharedPointer<IBinding>>> &bindingsByScript);
    void addBindingPages(const IBinding &binding);
    void addScriptPages(BotScript *botScript, const QList<QSharedPointer<IBinding>> &bindings, bool isAdmin);
    void addPages(BotScript *botScript, const QList<QSharedPointer<IBinding>> &bindings);

    bool canAddToPage(const QString &name, const QString &description, int fieldCount, int characterCount);
    void buildScriptPage(QList<Embed> &scriptPages, Embed &page, const QString &name, const QString &descriptionShort, int &fieldCount, int &characterCount);
    void appendBindingNames(QString &descriptionShort, const QList<QSharedPointer<IBinding> > bindings);
public:

    static const QString INVALID_HELP;

    UserHelp(QObject *parent = nullptr) : QObject{parent} {}
    UserHelp(const UserHelp &other) : QObject{other.parent()}, _pages{other._pages} {}
    UserHelp(const QMap<BotScript*, QList<QSharedPointer<IBinding>>> &bindingsByScript,
             const QString &userId,
             const QString &channelId,
             const QString &guildId,
             bool isAdmin,
             QObject *parent = nullptr);

    const Embed getHelpPage(const QString &pageName, int pageNum);
    const QString& getChannelId();
    const QString &getGuildId();

    void clear();
};

#endif // USERHELP_H
