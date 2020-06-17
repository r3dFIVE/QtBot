#include "tst_properties.h"

#include <payloads/properties.h>

#include <QJsonObject>

void
PropertiesTest::test_serialization() {
    Properties properties;

    QJsonObject serializedProperties = properties.toQJsonObject();

    QVERIFY(serializedProperties[properties.OS] == QSysInfo::productType());

    QVERIFY(serializedProperties[properties.BROWSER] == "QtBot");

    QVERIFY(serializedProperties[properties.DEVICE] == "QtBot");
}

void
PropertiesTest::test_deserialization() {
    // N/A
}

static PropertiesTest PROPERTIES_TEST;
