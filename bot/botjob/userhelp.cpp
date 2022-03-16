#include "userhelp.h"

void
UserHelp::addPages(BotScript *botScript, const IBinding &binding) {
    qDebug() << binding.metaObject()->className();
}

//void
//UserHelp::addBindingPages(const HelpPage &page) {

//}

void
UserHelp::addScriptPages(BotScript *botScript) {

}

QStringList
UserHelp::splitDescription(const QString &description) {
    QString tmp(description);

    QStringList tokens;

    while (!tmp.isEmpty()) {
        tokens.append(tmp.left(Embed::DECRIPTION_MAX_LENGTH));

        tmp.remove(0, Embed::DECRIPTION_MAX_LENGTH);
    }

    return tokens;
}
