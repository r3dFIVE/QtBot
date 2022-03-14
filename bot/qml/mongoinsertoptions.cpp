#include "mongoinsertoptions.h"

const QString MongoInsertOptions::BYPASS_DOCUMENT_VALIDATION = QString("bypass_document_validation");
const QString MongoInsertOptions::ORDERED = QString("ordered");

MongoInsertOptions::MongoInsertOptions(const MongoInsertOptions &other, QObject *parent) : QObject(parent) {
    _insertOptions = other._insertOptions;
}

MongoInsertOptions&
MongoInsertOptions::operator=(const MongoInsertOptions &other) {
    if (this == &other) {
        return *this;
    }

    _insertOptions = other._insertOptions;

    return *this;
}

mongocxx::options::insert
MongoInsertOptions::fromJson(const QJsonObject &options) {
    mongocxx::options::insert insertOptions{};

    if (options.contains(BYPASS_DOCUMENT_VALIDATION)) {
        auto bypass = options[BYPASS_DOCUMENT_VALIDATION].toBool();

        insertOptions.bypass_document_validation(bypass);
    }

    if (options.contains(ORDERED)) {
        auto ordered = options[ORDERED].toBool();

        insertOptions.ordered(ordered);
    }

    return insertOptions;
}

mongocxx::options::insert
MongoInsertOptions::fromVariant(const QVariant &options) {
    mongocxx::options::insert insertOptions{};

    if (options.isValid())  {
        auto insert = qvariant_cast<MongoInsertOptions*>(options);

        if (insert) {
            insertOptions = insert->get();
        }
    } else {
        getLogger()->warning(QString("Failed to set Mongo Insert Options: %1").arg(options.toString()));

        insertOptions = mongocxx::options::insert{};
    }

    return insertOptions;
}

bool
MongoInsertOptions::bypassDocumentValidation() {
    bool allow = false;

    auto result = _insertOptions.bypass_document_validation();

    if (result) {
        allow = result.value();
    }

    return allow;
}

void
MongoInsertOptions::bypassDocumentValidation(const bool bypass) {
    _insertOptions.bypass_document_validation(bypass);
}

bool
MongoInsertOptions::ordered() {
    bool ordered = false;

    auto result = _insertOptions.bypass_document_validation();

    if (result) {
        ordered = result.value();
    }

    return ordered;
}

void
MongoInsertOptions::ordered(const bool ordered) {
    _insertOptions.bypass_document_validation(ordered);
}

mongocxx::options::insert
MongoInsertOptions::get() {
    return _insertOptions;
}
