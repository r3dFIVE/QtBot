#include "mongohint.h"

#include "util/mongoutils.h"


MongoHint::MongoHint(const MongoHint &other) {
    _hint = QSharedPointer<mongocxx::hint>(new mongocxx::hint{*other._hint.get()});
}

MongoHint::MongoHint(const QJsonObject &hint) {
    _hint = QSharedPointer<mongocxx::hint>(new mongocxx::hint{MongoUtils::toViewOrValue(hint)});
}

MongoHint&
MongoHint::operator=(const MongoHint &other) {
    if (this == &other) {
        return *this;
    }

    _hint = QSharedPointer<mongocxx::hint>(new mongocxx::hint{*other._hint.get()});

    return *this;
}

QJsonObject
MongoHint::toValue() {
    return MongoUtils::toJson(_hint->to_value());
}
