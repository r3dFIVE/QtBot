#include "tst_secrets.h"
#include "testpayloads.h"

#include <payloads/secrets.h>

void
SecretsTest::test_serialization_minimal() {
    Secrets secrets;

    QJsonObject serializedSecrets = secrets.toQJsonObject();

    QVERIFY(!serializedSecrets.contains(secrets.JOIN));
    QVERIFY(!serializedSecrets.contains(secrets.SPECTATE));
    QVERIFY(!serializedSecrets.contains(secrets.MATCH));
}

void
SecretsTest::test_serialization_full() {
    Secrets secrets;
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
SecretsTest::test_deserialization_minimal() {
    Secrets secrets;
    secrets.fromQString(PLD_SECRETS_MINIMAL);

    QVERIFY(secrets.join == "");
    QVERIFY(secrets.join != TEST_STRING1);

    QVERIFY(secrets.spectate == "");
    QVERIFY(secrets.spectate != TEST_STRING1);

    QVERIFY(secrets.match == "");
    QVERIFY(secrets.match != TEST_STRING1);
}

void
SecretsTest::test_deserialization_full() {
    Secrets secrets;
    secrets.fromQString(PLD_SECRETS_FULL);

    QVERIFY(secrets.join != "");
    QVERIFY(secrets.join == TEST_STRING1);

    QVERIFY(secrets.spectate != "");
    QVERIFY(secrets.spectate == TEST_STRING2);

    QVERIFY(secrets.match != "");
    QVERIFY(secrets.match == TEST_STRING1);
}

static SecretsTest SECRETS_TEST;
