#include "mongoupdateoptions.h"

#include "logging/logfactory.h"
#include "util/mongoutils.h"


const QString MongoUpdateOptions::BYPASS_DOCUMENT_VALIDATION = QString("bypass_document_validation");
const QString MongoUpdateOptions::COLLATION = QString("collation");
const QString MongoUpdateOptions::UPSERT = QString("upsert");
const QString MongoUpdateOptions::HINT = QString("hint");

MongoUpdateOptions::MongoUpdateOptions(const MongoUpdateOptions &other, QObject *parent) : QObject(parent) {
    _updateOptions = other._updateOptions;
}

MongoUpdateOptions&
MongoUpdateOptions::operator=(const MongoUpdateOptions &other) {
    if (this == &other) {
        return *this;
    }

    _updateOptions = other._updateOptions;

    return *this;
}

mongocxx::options::update
MongoUpdateOptions::fromJson(const QJsonObject &options) {
    mongocxx::options::update updateOptions{};

    if (options.contains(BYPASS_DOCUMENT_VALIDATION)) {
        auto bypass = options[BYPASS_DOCUMENT_VALIDATION].toBool();

        updateOptions.bypass_document_validation(bypass);
    }

    if (options.contains(COLLATION)) {
        auto collation = options[COLLATION].toObject();

        updateOptions.collation(MongoUtils::toViewOrValue(collation));
    }

    if (options.contains(UPSERT)) {
        auto upsert = options[UPSERT].toBool();

        updateOptions.upsert(upsert);
    }

    if (options.contains(HINT)) {
        auto hint = options[HINT].toObject();

        updateOptions.hint(mongocxx::hint{MongoUtils::toViewOrValue(hint)});
    }

    return updateOptions;
}

mongocxx::options::update
MongoUpdateOptions::fromVariant(const QVariant &options) {
    mongocxx::options::update updateOptions{};

    if (options.isValid())  {
        auto find = qvariant_cast<MongoUpdateOptions*>(options);

        if (find) {
            updateOptions = find->get();
        }
    } else {
        LogFactory::getLogger()->warning(QString("Failed to set Mongo Update Options: %1").arg(options.toString()));

        updateOptions = mongocxx::options::update{};
    }

    return updateOptions;
}

void
MongoUpdateOptions::bypassDocumentValidation(const bool bypass) {
    _updateOptions.bypass_document_validation(bypass);
}

bool
MongoUpdateOptions::bypassDocumentValidation() {
    bool bypass = false;

    auto result = _updateOptions.bypass_document_validation();

    if (result) {
        bypass = result.get();
    }

    return bypass;
}

void
MongoUpdateOptions::collation(const QJsonObject &json) {
    _updateOptions.collation(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoUpdateOptions::collation() {
    QJsonObject json;

    auto result = _updateOptions.collation();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

void
MongoUpdateOptions::upsert(const bool upsert) {
    _updateOptions.upsert(upsert);
}

bool
MongoUpdateOptions::upsert() {
    bool bypass = false;

    auto result = _updateOptions.bypass_document_validation();

    if (result) {
        bypass = result.get();
    }

    return bypass;
}

void
MongoUpdateOptions::hint(const QJsonObject &json) {
    _updateOptions.hint(mongocxx::hint{MongoUtils::toViewOrValue(json)});
}

QJsonObject
MongoUpdateOptions::hint() {
    QJsonObject json;

    auto result = _updateOptions.hint();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

mongocxx::options::update
MongoUpdateOptions::get() {
    return _updateOptions;
}

