#include "userhelp.h"

void
UserHelp::addPages(BotScript *botScript, const IBinding &binding) {
    qDebug() << binding.metaObject()->className();
}

void
UserHelp::clear() {
    _pages.clear();
}

void
UserHelp::addBindingPages(const IBinding &binding) {
    QString description = binding.getDescription();

    QString type = binding.metaObject()->className();

    QString name = binding.getName();

    if (description.isEmpty()) {
        _pages[type][name] << buildPage(name, description, 1, 1);
    }

    QStringList descriptionTokens = splitDescription(description);

    for (int i = 0; i < descriptionTokens.size(); ++i) {
        _pages[type][name] << buildPage(name, description, i + 1, descriptionTokens.size());
    }
}

Embed
UserHelp::buildPage(const QString &name, const QString &description, int pageNum, int total) {
    EmbedAuthor author;

    QString authorStr = QString("%1 <%2/%3>");

    author.setName(authorStr
                   .arg(name)
                   .arg(pageNum)
                   .arg(total));

    Embed page;

    page.setAuthor(author.object());

    page.setDescription(description);

    return page;
}

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
