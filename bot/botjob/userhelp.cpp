#include "userhelp.h"

UserHelp::UserHelp(const QHash<BotScript*, QList<QSharedPointer<IBinding>>> &bindingsByScript, QObject *parent) : QObject{parent} {
    QHashIterator<BotScript*, QList<QSharedPointer<IBinding>>> it(bindingsByScript);

    while(it.hasNext()) {
        it.next();

        addScriptPages(it.key(), it.value());
    }

    addMainPages(bindingsByScript.keys());
}

const Embed
UserHelp::getHelpPage(const QString &pageName, int pageNum) {
    if (!_pages.contains(pageName)) {
        _logger->warning(QString("TODO add failed embed, pageName does not exist"));

        return Embed();
    }

    if (pageNum > 0 && _pages[pageName].size() > pageNum - 1) {
        _logger->warning(QString("TODO add failed embed, pageNum out of bound for pageName"));

        return Embed();
    }

    return _pages[pageName].at(pageNum);
}

void
UserHelp::clear() {
    _pages.clear();
}

void
UserHelp::addBindingPages(const IBinding &binding) {
    QString description = binding.getDescription();

    QString name = binding.getName();

    if (description.isEmpty()) {
        _pages[name] << buildBindingPage(name, description, 1, 1);
    }

    QStringList descriptionTokens = splitDescription(description);

    for (int i = 0; i < descriptionTokens.size(); ++i) {
        _pages[name] << buildBindingPage(name, description, i + 1, descriptionTokens.size());
    }
}

void addScriptPage() {

}

void
UserHelp::addScriptPages(BotScript *botScript, const QList<QSharedPointer<IBinding>> &bindings) {
    if (!botScript) {
        _logger->info("TODO - Implement CoreCommand Bot Help!!!");

        return;
    }

    QList<Embed> scriptPages;

    QStringList descriptionTokens = splitDescription(botScript->getDescription());

    for (auto &token : descriptionTokens) {
        Embed scriptPage;

        scriptPage.setDescription(token);

        scriptPages << scriptPage;
    }

    Embed page;

    if (scriptPages.size() > 0) {
        page = scriptPages.last();

        scriptPages.removeLast();
    }

    int characterCount = page.getDescription().toString().length() + Embed::AUTHOR_NAME_MAX_LENGTH;

    int fieldCount = 0;

    for (auto &binding : bindings) {
        addBindingPages(*binding);

        QString descriptionShort = binding->getDescriptionShort();

        QString name = QString("%1 (%2)")
                .arg(binding->getName())
                .arg(binding->metaObject()->className());

        buildScriptPage(scriptPages, page, name, descriptionShort, fieldCount, characterCount);
    }

    scriptPages << page;

    for (int i = 0; i < scriptPages.size(); ++i) {
        EmbedAuthor author;

        QString authorStr = QString("%1 <%2/%3>")
                .arg(botScript->getName())
                .arg(i + 1)
                .arg(scriptPages.size());

        author.setName(authorStr);

        scriptPages[i].setAuthor(author.object());
    }

    _pages[botScript->getName()] = scriptPages;
}

void
UserHelp::buildScriptPage(QList<Embed> &scriptPages,
                          Embed &page,
                          const QString &name,
                          const QString &descriptionShort,
                          int &fieldCount,
                          int &characterCount) {
    if (name.isEmpty() || descriptionShort.isEmpty()) {
        _logger->warning(QString("Name (\"%1\") or descriptionShort (\"%2\") cannot be empty, skipping help field")
                            .arg(name, descriptionShort));

        return;
    }

    if (name.length() + descriptionShort.length() + characterCount > Embed::TOTAL_MAX_LENGTH
        || fieldCount == Embed::FIELDS_MAX - 1) {

        characterCount = 0;

        fieldCount = 0;

        scriptPages << page;

        page = Embed();
    }

    EmbedField field;

    field.setInline(false);

    field.setName(name);

    characterCount += name.length();

    field.setValue(descriptionShort);

    characterCount += descriptionShort.length();

    page.addField(field.object());

    fieldCount++;
}

Embed
UserHelp::buildBindingPage(const QString &name, const QString &description, int pageNum, int total) {
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

void
UserHelp::addMainPages(QList<BotScript*> botScripts) {
    int characterCount = 0;

    int fieldCount = 0;

    Embed page;

    QList<Embed> mainPages;

    for (auto &botScript : botScripts) {
        if (!botScript) {
            _logger->warning(QString("TODO handle null botscript mainPages"));

            continue;
        }

        QString name = botScript->getName();

        QString descriptionShort = botScript->getDescriptionShort();

        buildScriptPage(mainPages, page, name, descriptionShort, fieldCount, characterCount);
    }

    mainPages << page;

    for (int i = 0; i < mainPages.size(); ++i) {
        EmbedAuthor author;

        QString authorString = QString(".help <%1/%2>")
                .arg(i + 1)
                .arg(mainPages.size());

        author.setName(authorString);

        mainPages[i].setAuthor(author.object());
    }

    QString pageName;

    _pages[pageName] = mainPages;
}
