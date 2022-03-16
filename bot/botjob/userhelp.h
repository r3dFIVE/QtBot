#ifndef USERHELP_H
#define USERHELP_H

#include <QObject>

#include "botscript.h"
#include "ibinding.h"
#include "payloads/embed.h"


class UserHelp : public QObject
{
    Q_OBJECT

    QMap<QString, QMap<QString, QList<Embed>>> _pages;

    Embed buildPage(const QString &name, const QString &description, int pageNum, int total);
    QStringList splitDescription(const QString &description);

    void addBindingPages(const IBinding &binding);
    void addScriptPages(BotScript *botScript);

public:
    explicit UserHelp(QObject *parent = nullptr) : QObject(parent) {}

    void addPages(BotScript *botScript, const IBinding &binding);

    void clear();
};

#endif // USERHELP_H
