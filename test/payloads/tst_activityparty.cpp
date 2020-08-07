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
