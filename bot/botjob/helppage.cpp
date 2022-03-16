#include "helppage.h"

const QString HelpPage::DESCRIPTION = "description";
const QString HelpPage::DESCRIPTION_SHORT = "short_description";

QString
HelpPage::getDescription() const {
    return _description;
}

void
HelpPage::setDescription(const QString &description) {
    _description = description;
}

QString
HelpPage::getDescriptionShort() const {
    return _descriptionShort.isEmpty() ? _description : _descriptionShort;
}

void
HelpPage::setDescriptionShort(const QString &description) {
    _descriptionShort = description;
}

QString
HelpPage::getName() const {
    return _name;
}

void
HelpPage::setName(const QString &name) {
    _name = name;
}
