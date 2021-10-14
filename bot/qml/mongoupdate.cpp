#include "mongoupdate.h"


MongoUpdate::MongoUpdate(const MongoUpdate &other, QObject *parent) : QObject(parent) {
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

