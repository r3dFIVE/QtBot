#include "mongoupdate.h"

const QString MongoUpdate::TYPE_NAME = "MongoUpdate";

MongoUpdate::MongoUpdate(const MongoUpdate &other) {
    _updateOpts = other._updateOpts;
}

MongoUpdate&
MongoUpdate::operator=(const MongoUpdate &other) {
    if (this == &other) {
        return *this;
    }

    _updateOpts = other._updateOpts;

    return *this;
}



mongocxx::options::update
MongoUpdate::get() {
    return _updateOpts;
}

