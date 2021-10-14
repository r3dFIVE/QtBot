#include "mongoinsert.h"


MongoInsert::MongoInsert(const MongoInsert &other, QObject *parent) : QObject(parent) {
    _insertOpts = other._insertOpts;
}

MongoInsert&
MongoInsert::operator=(const MongoInsert &other) {
    if (this == &other) {
        return *this;
    }

    _insertOpts = other._insertOpts;

    return *this;
}

bool
MongoInsert::bypassDocumentValidation() {
    bool allow = false;

    auto result = _insertOpts.bypass_document_validation();

    if (result) {
        allow = result.value();
    }

    return allow;
}

void
MongoInsert::bypassDocumentValidation(const bool bypass) {
    _insertOpts.bypass_document_validation(bypass);
}

bool
MongoInsert::ordered() {
    bool ordered = false;

    auto result = _insertOpts.bypass_document_validation();

    if (result) {
        ordered = result.value();
    }

    return ordered;
}

void
MongoInsert::ordered(const bool ordered) {
    _insertOpts.bypass_document_validation(ordered);
}

mongocxx::options::insert
MongoInsert::get() {
    return _insertOpts;
}
