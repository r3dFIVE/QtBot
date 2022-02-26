/**
 *
 *
 * Original credit to https://github.com/lagner/QGumboParser
 *
 * DOMParsing code borrows _heavily_ from here!
 */


#include "domattribute.h"
#include <stdexcept>


DOMAttribute::DOMAttribute(const char* n, const char* value, QObject *parent) : QObject(parent) {
    if (!n) {
        std::invalid_argument("attribute name can't be empty");
    }

    _name = QString::fromUtf8(n);

    if (value) {
        _value = QString::fromUtf8(value);
    }
}

DOMAttribute::DOMAttribute(const DOMAttribute &other, QObject *parent) : QObject(parent) {
    if (this == &other) {
        return;
    }

    _name = other._name;

    _value = other._value;
}
