#include "userhelp.h"

const QString UserHelp::COMMA_SPACE = QString(", ");
const QString UserHelp::INVALID_HELP = QString("Invalid Help Page");
const QString UserHelp::HELP_COMMAND = QString(".help");
const QString UserHelp::HELP_USAGE = QString("\n\n**Usage:**\n\n*%1 <pageNum>*\n*%1 <script/bindingName> <pageNum>*").arg(UserHelp::HELP_COMMAND);

UserHelp::UserHelp(const QMap<BotScript*, QList<QSharedPointer<IBinding>>> &bindingsByScript,
                   const QString &userId,
                   const QString &channelId,
                   const QString &guildId,
                   bool isAdmin,
                   QObject *parent) : QObject{parent} {
    QMapIterator<BotScript*, QList<QSharedPointer<IBinding>>> it(bindingsByScript);

    _userId = userId;

    _channelId = channelId;

    _guildId = guildId;

    while(it.hasNext()) {
        it.next();

        addScriptPages(it.key(), it.value(), isAdmin);
    }

    addMainPages(bindingsByScript);
}

const Embed
UserHelp::getHelpPage(const QString &pageName, int pageNum) {
    if (_pages.isEmpty()) {
        QString errorString = QString("You do not have access to any scripts/bindings in this channel.");

        _logger->debug(QString("%1 userId: %2, channelId: %3")
                       .arg(errorString)
                       .arg(_userId)
                       .arg(_channelId));

        return Embed(UserHelp::INVALID_HELP, QString("%1%2")
                     .arg(errorString)
                     .arg(UserHelp::HELP_USAGE));
    }


    if (!_pages.contains(pageName)) {
        QString errorString = QString("Script/Binding Name: `%1`, does not exist or you do not have access.")
                .arg(pageName);

        _logger->debug(QString("%1 userId: %2, channelId: %3")
                       .arg(errorString)
                       .arg(_userId)
                       .arg(_channelId));

        return Embed(UserHelp::INVALID_HELP, QString("%1%2")
                     .arg(errorString)
                     .arg(UserHelp::HELP_USAGE));
    }

    if (pageNum > 0 && _pages[pageName].size() <= pageNum) {
        QString errorString = QString("Invalid page number: `%1`, for Script/Binding Name: `%2`")
                .arg(pageNum + 1)
                .arg(pageName.isEmpty() ? ".help" : pageName);

        _logger->debug(errorString);

        return Embed(UserHelp::INVALID_HELP, QString("%1%2")
                     .arg(errorString)
                     .arg(UserHelp::HELP_USAGE));
    }

    return _pages[pageName].at(pageNum);
}

const QString&
UserHelp::getChannelId() {
    return _channelId;
}

const QString&
UserHelp::getGuildId() {
    return _guildId;
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

void
UserHelp::addScriptPages(BotScript *botScript,
                         const QList<QSharedPointer<IBinding>> &bindings,
                         bool isAdmin) {
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

        QString descriptionShort = QString("*%1*")
                .arg(binding->getDescriptionShort());

        QString name = QString("%1").arg(binding->getName());

        if (isAdmin) {
            name = QString("%1 (%2)")
                .arg(name)
                .arg(binding->metaObject()->className());
        }

        buildScriptPage(scriptPages, page, name, descriptionShort, fieldCount, characterCount);
    }

    scriptPages << page;

    for (int i = 0; i < scriptPages.size(); ++i) {
        QString descriptionString = QString("```%1 <%2/%3>```\n%4")
                .arg(botScript->getName())
                .arg(i + 1)
                .arg(scriptPages.size())
                .arg(scriptPages[i].getDescription().toString());

        scriptPages[i].setDescription(descriptionString);
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
        || fieldCount == Embed::FIELDS_MAX) {

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
    QString descriptionString = QString("```%1 <%2/%3>```\n%4")
            .arg(name)
            .arg(pageNum)
            .arg(total)
            .arg(description);

    Embed page;

    page.setDescription(descriptionString);

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
UserHelp::addMainPages(const QMap<BotScript*, QList<QSharedPointer<IBinding>>> &bindingsByScript) {
    if (bindingsByScript.size() == 0) {
        return;
    }

    int characterCount = 0;

    int fieldCount = 0;

    Embed page;

    QList<Embed> mainPages;

    QMapIterator<BotScript*, QList<QSharedPointer<IBinding>>> it(bindingsByScript);

    QList<BotScript*> scripts = bindingsByScript.keys();

    scripts.removeAll(nullptr);

    std::sort(scripts.begin(), scripts.end(), [&](BotScript* a, BotScript *b) {
        return a->getName() < b->getName();
    });

    for(auto& botScript : scripts) {
        if (!botScript) {
            _logger->debug(QString("TODO handle CoreCommand (null) BotScript mainPages"));

            continue;
        }

        QString name = botScript->getName();

        QString descriptionShort = botScript->getDescriptionShort();

        appendBindingNames(descriptionShort, bindingsByScript[botScript]);

        buildScriptPage(mainPages, page, name, descriptionShort, fieldCount, characterCount);
    }

    mainPages << page;

    QString firstPageDescription = QString(HELP_USAGE).replace("*", "");

    for (int i = 0; i < mainPages.size(); ++i) {
        QString descriptionString = QString("```%1 <%2/%3>%4```")
                .arg(HELP_COMMAND)
                .arg(i + 1)
                .arg(mainPages.size())
                .arg(firstPageDescription);

        firstPageDescription.clear();

        mainPages[i].setDescription(descriptionString);
    }

    QString pageName;

    _pages[pageName] = mainPages;
}

void
UserHelp::appendBindingNames(QString &descriptionShort, const QList<QSharedPointer<IBinding>> bindings) {
    descriptionShort.append("\n\n*");

    int characterCount = descriptionShort.length();

    for (auto& binding : bindings) {
        int newCount = characterCount + binding->getName().length() + COMMA_SPACE.length();

        if (newCount <= Embed::FIELDS_VALUE_MAX_LENGTH) {
            characterCount = newCount;

            descriptionShort.append(binding->getName());

            descriptionShort.append(COMMA_SPACE);

        } else {
            descriptionShort.append("...");

            break;
        }
    }

    descriptionShort = descriptionShort.length() > 0 ? descriptionShort.trimmed().chopped(1) : descriptionShort;

    descriptionShort.append("*");
}
