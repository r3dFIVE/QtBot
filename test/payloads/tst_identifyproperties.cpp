#include "tst_identifyproperties.h"

#include <payloads/identifyproperties.h>

#include <QJsonObject>

void
IdentifyPropertiesTest::test_serialization() {
    IdentifyProperties properties;

    QJsonObject serializedProperties = properties.toQJsonObject();

    QVERIFY(serializedProperties[properties.OS] == QSysInfo::productType());

    QVERIFY(serializedProperties[properties.BROWSER] == "QtBot");

    QVERIFY(serializedProperties[properties.DEVICE] == "QtBot");
}

void
IdentifyPropertiesTest::test_deserialization() {
    // N/A
}

static IdentifyPropertiesTest IDENTIFY_PROPERTIES_TEST;
