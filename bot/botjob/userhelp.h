#ifndef USERHELP_H
#define USERHELP_H

#include <QObject>

#include "botscript.h"
#include "ibinding.h"
#include "payloads/embed.h"


class UserHelp : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);

    QMap<QString, QList<Embed>> _pages;

    Embed buildBindingPage(const QString &name, const QString &description, int pageNum, int total);
    QStringList splitDescription(const QString &description);

    void addMainPages(QList<BotScript*> botScripts);
    void addBindingPages(const IBinding &binding);
    void addScriptPages(BotScript *botScript, const QList<QSharedPointer<IBinding>> &bindings);
    void addPages(BotScript *botScript, const QList<QSharedPointer<IBinding>> &bindings);

    bool canAddToPage(const QString &name, const QString &description, int fieldCount, int characterCount);
    void buildScriptPage(QList<Embed> &scriptPages, Embed &page, const QString &name, const QString &descriptionShort, int &fieldCount, int &characterCount);
public:

    UserHelp(QObject *parent = nullptr) : QObject{parent} {}
    UserHelp(const UserHelp &other) : _pages{other._pages} {}
    UserHelp(const QHash<BotScript*, QList<QSharedPointer<IBinding>>> &bindingsByScript, QObject *parent = nullptr);

    const Embed getHelpPage(const QString &pageName, int pageNum);

    void clear();
};

#endif // USERHELP_H
