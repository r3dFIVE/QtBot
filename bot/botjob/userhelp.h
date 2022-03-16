#ifndef USERHELP_H
#define USERHELP_H

#include <QObject>

#include "botscript.h"
#include "ibinding.h"
#include "payloads/embed.h"


class UserHelp : public QObject
{
    Q_OBJECT

    QList<Embed> mainPages;
    QMap<QString, QMap<QString, QList<Embed>>> childPages;

    QStringList splitDescription(const QString &description);

    void addBindingPages(const IBinding &binding);
    void addScriptPages(BotScript *botScript);


    Embed buildPage(const IBinding &binding);
public:
    explicit UserHelp(QObject *parent = nullptr) : QObject(parent) {}

    void addPages(BotScript *botScript, const IBinding &binding);


};

#endif // USERHELP_H
