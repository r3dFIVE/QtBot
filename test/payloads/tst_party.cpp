#include "tst_party.h"
#include "testpayloads.h"

#include <payloads/party.h>


void
PartyTest::test_serialization_minimal() {
    Party party;

    QJsonObject serializedParty = party.toQJsonObject();

    QVERIFY(!serializedParty.contains(party.ID));
    QVERIFY(!serializedParty.contains(party.SIZE));
}

void
PartyTest::test_serialization_full() {
    Party party;
    party.id = TEST_STRING1;
    party.size[0] = QSharedPointer<int>(new int(TEST_INT1));
    party.size[1] = QSharedPointer<int>(new int(TEST_INT2));

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
PartyTest::test_deserialization_minimal() {
    Party party;
    party.fromQString(PLD_PARTY_MINIMAL);

    QVERIFY(party.id == nullptr);

    QVERIFY(party.size[0] == nullptr);

    QVERIFY(party.size[1] == nullptr);
}

void
PartyTest::test_deserialization_full() {
    Party party;
    party.fromQString(PLD_PARTY_FULL);

    QVERIFY(party.id == TEST_STRING1);

    QVERIFY(*party.size[0] == TEST_INT1);
    QVERIFY(*party.size[0] != TEST_INT2);

    QVERIFY(*party.size[1] != TEST_INT1);
    QVERIFY(*party.size[1] == TEST_INT2);
}

static PartyTest PARTY_TEST;