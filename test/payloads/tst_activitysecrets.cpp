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

    secrets.setJoin(TEST_STRING1);

    secrets.setSpectate(TEST_STRING2);

    secrets.setMatch(TEST_STRING1);

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
    ActivitySecrets secrets(PLD_ACTIVITY_SECRETS_MINIMAL);

    QVERIFY(secrets.getJoin() == "");
    QVERIFY(secrets.getJoin() != TEST_STRING1);
    QVERIFY(secrets.getSpectate() == "");
    QVERIFY(secrets.getSpectate() != TEST_STRING1);
    QVERIFY(secrets.getMatch() == "");
    QVERIFY(secrets.getMatch() != TEST_STRING1);
}

void
ActivitySecretsTest::test_deserialization_full() {
    ActivitySecrets secrets(PLD_ACTIVITY_SECRETS_FULL);

    QVERIFY(secrets.getJoin() != "");
    QVERIFY(secrets.getJoin() == TEST_STRING1);
    QVERIFY(secrets.getSpectate() != "");
    QVERIFY(secrets.getSpectate() == TEST_STRING2);
    QVERIFY(secrets.getMatch() != "");
    QVERIFY(secrets.getMatch() == TEST_STRING1);
}

static ActivitySecretsTest SECRETS_TEST;
