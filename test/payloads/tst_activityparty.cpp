/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "tst_activityparty.h"
#include "testpayloads.h"
#include "payloads/activityparty.h"

void
ActivityPartyTest::test_serialization_minimal() {
    ActivityParty party;

    QJsonObject serializedParty = party.toQJsonObject();

    QVERIFY(!serializedParty.contains(party.ID));
    QVERIFY(!serializedParty.contains(party.SIZE));
}

void
ActivityPartyTest::test_serialization_full() {
    ActivityParty party;

    party.setId(TEST_STRING1);

    QJsonArray size = { TEST_INT1, TEST_INT2 };

    party.setSize(size);

    QJsonObject serializedParty = party.toQJsonObject();

    QVERIFY(serializedParty.contains(party.ID));
    QVERIFY(serializedParty[party.ID] == TEST_STRING1);
    QVERIFY(serializedParty.contains(party.SIZE));

    QJsonArray sizeArray = serializedParty[party.SIZE].toArray();

    QVERIFY(sizeArray[0] == TEST_INT1);
    QVERIFY(sizeArray[0] != TEST_INT2);
    QVERIFY(sizeArray[1] != TEST_INT1);
    QVERIFY(sizeArray[1] == TEST_INT2);
}

void
ActivityPartyTest::test_deserialization_minimal() {
    ActivityParty party(PLD_ACTIVITY_PARTY_MINIMAL);

    QJsonObject serializedParty = party.toQJsonObject();

    QVERIFY(!serializedParty.contains(party.ID));
    QVERIFY(!serializedParty.contains(party.SIZE));
}

void
ActivityPartyTest::test_deserialization_full() {
    ActivityParty party(PLD_ACTIVITY_PARTY_FULL);

    QVERIFY(party.getId() == TEST_STRING1);
    QVERIFY(party.getSize()[0] == TEST_INT1);
    QVERIFY(party.getSize()[0] != TEST_INT2);
    QVERIFY(party.getSize()[1] != TEST_INT1);
    QVERIFY(party.getSize()[1] == TEST_INT2);
}

static ActivityPartyTest ACTIVITY_PARTY_TEST;
