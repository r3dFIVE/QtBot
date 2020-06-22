#include "tst_activitysecrets.h"
#include "testpayloads.h"

#include <payloads/activitysecrets.h>

void
ActivitySecretsTest::test_serialization_minimal() {
    ActivitySecrets secrets;

    QJsonObject serializedSecrets = secrets.toQJsonObject();

    QVERIFY(!serializedSecrets.contains(secrets.JOIN));
    QVERIFY(!serializedSecrets.contains(secrets.SPECTATE));
    QVERIFY(!serializedSecrets.contains(secrets.MATCH));
}

void
ActivitySecretsTest::test_serialization_full() {
    ActivitySecrets secrets;
    secrets.join = TEST_STRING1;
    secrets.spectate = TEST_STRING2;
    secrets.match = TEST_STRING1;

    QJsonObject serializedSecrets = secrets.toQJsonObject();

    QVERIFY(serializedSecrets[secrets.JOIN] == TEST_STRING1);
    QVERIFY(serializedSecrets[secrets.JOIN] != TEST_STRING2);

    QVERIFY(serializedSecrets[secrets.SPECTATE] != TEST_STRING1);
    QVERIFY(serializedSecrets[secrets.SPECTATE] == TEST_STRING2);

    QVERIFY(serializedSecrets[secrets.MATCH] == TEST_STRING1);
    QVERIFY(serializedSecrets[secrets.MATCH] != TEST_STRING2);
}

void
ActivitySecretsTest::test_deserialization_minimal() {
    ActivitySecrets secrets;
    secrets.fromQString(PLD_ACTIVITY_SECRETS_MINIMAL);

    QVERIFY(secrets.join == "");
    QVERIFY(secrets.join != TEST_STRING1);

    QVERIFY(secrets.spectate == "");
    QVERIFY(secrets.spectate != TEST_STRING1);

    QVERIFY(secrets.match == "");
    QVERIFY(secrets.match != TEST_STRING1);
}

void
ActivitySecretsTest::test_deserialization_full() {
    ActivitySecrets secrets;
    secrets.fromQString(PLD_ACTIVITY_SECRETS_FULL);

    QVERIFY(secrets.join != "");
    QVERIFY(secrets.join == TEST_STRING1);

    QVERIFY(secrets.spectate != "");
    QVERIFY(secrets.spectate == TEST_STRING2);

    QVERIFY(secrets.match != "");
    QVERIFY(secrets.match == TEST_STRING1);
}

static ActivitySecretsTest SECRETS_TEST;
