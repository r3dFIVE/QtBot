/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
