#include "mongodeleteoptions.h"

#include <QVariant>

#include "logging/logfactory.h"

#include "util/mongoutils.h"


const QString MongoDeleteOptions::COLLATION = QString("collation");
const QString MongoDeleteOptions::HINT = QString("hint");

MongoDeleteOptions::MongoDeleteOptions(const MongoDeleteOptions &other, QObject *parent) : QObject(parent) {
    if (this == &other) {
        return;
    }

    _deleteOptions = other._deleteOptions;
}



mongocxx::options::delete_options
MongoDeleteOptions::fromJson(const QJsonObject &options) {
    mongocxx::options::delete_options deleteOptions{};

    if (options.contains(COLLATION)) {
        auto collation = options[COLLATION].toObject();

        deleteOptions.collation(MongoUtils::toViewOrValue(collation));
    }

    if (options.contains(HINT)) {
        auto hint = options[HINT].toObject();

        deleteOptions.hint(mongocxx::hint{MongoUtils::toViewOrValue(hint)});
    }

    return deleteOptions;
}

mongocxx::options::delete_options
MongoDeleteOptions::fromVariant(const QVariant &options) {
    mongocxx::options::delete_options deleteOptions{};

    if (options.isValid())  {
        auto find = qvariant_cast<MongoDeleteOptions*>(options);

        if (find) {
            deleteOptions = find->get();
        }
    } else {
        LogFactory::getLogger()->warning(QString("Failed to set Mongo Find Options: %1").arg(options.toString()));

        deleteOptions = mongocxx::options::delete_options{};
    }

    return deleteOptions;
}

void
MongoDeleteOptions::collation(const QJsonObject &json) {
    _deleteOptions.collation(MongoUtils::toViewOrValue(json));
}

QJsonObject
MongoDeleteOptions::collation() const {
    return MongoUtils::toJson(_deleteOptions.collation().value());
}

void
MongoDeleteOptions::hint(const QJsonObject &json) {
    _deleteOptions.hint(mongocxx::hint{MongoUtils::toViewOrValue(json)});
}

QJsonObject
MongoDeleteOptions::hint() const {
    QJsonObject json;

    auto result = _deleteOptions.hint();

    if (result) {
        json = MongoUtils::toJson(result.value());
    }

    return json;
}

mongocxx::options::delete_options
MongoDeleteOptions::get() {
    return _deleteOptions;
}
