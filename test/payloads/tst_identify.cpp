#include "tst_identify.h"

#include "payloads/identify.h"
#include "payloads/identifyproperties.h"
#include "payloads/updatestatus.h"


void
IdentifyTest::test_deserialization_full() {
    Identify identify(PLD_IDENTIFY_FULL);

    QVERIFY(identify.getToken() == TEST_STRING1);
    QVERIFY(!identify.getProperties().isEmpty());

    IdentifyProperties properties(identify.getProperties());

    QVERIFY(identify.getCompress() == true);
    QVERIFY(identify.getLargeThreshold() == TEST_INT1);
    QVERIFY(identify.getShard()[0] == TEST_INT2);
    QVERIFY(identify.getShard()[1] == TEST_INT1);

    UpdateStatus presence(identify.getPresence());

    QVERIFY(presence.getSince() == TEST_INT1);
    QVERIFY(identify.getGuildSubscriptions() == true);
    QVERIFY(identify.getIntents() == TEST_INT2);
}

void
IdentifyTest::test_deserialization_minimal() {
    Identify identify;
    identify.fromQString(PLD_IDENTIFY_MINIMAL);

    QVERIFY(identify.getToken() == TEST_STRING1);

    IdentifyProperties properties(identify.getProperties());

    QVERIFY(properties.getBrowser() == "QtBot");
    QVERIFY(identify.getCompress().isUndefined());
    QVERIFY(identify.getLargeThreshold().isUndefined());
    QVERIFY(identify.getShard().isEmpty());
    QVERIFY(identify.getPresence().isEmpty());
    QVERIFY(identify.getGuildSubscriptions().isUndefined());
    QVERIFY(identify.getIntents().isUndefined());
}

void
IdentifyTest::test_serialization_full() {
    Identify identify;

    identify.setToken(TEST_STRING1);

    IdentifyProperties properties(PLD_PROPERTIES);

    identify.setProperties(properties.toQJsonObject());

    identify.setCompress(true);

    identify.setLargeThreshold(TEST_INT1);

    QJsonArray shard = { TEST_INT2, TEST_INT1};

    identify.setShard(shard);

    UpdateStatus presence;

    presence.fromQString(PLD_UPDATE_STATUS);

    identify.setPresence(presence.toQJsonObject());

    identify.setGuildSubscriptions(true);

    identify.setIntents(TEST_INT2);

    QJsonObject serializedIdentify = identify.toQJsonObject();

    QVERIFY(serializedIdentify[Identify::TOKEN] == TEST_STRING1);
    QVERIFY(serializedIdentify[Identify::PROPERTIES].toObject()[IdentifyProperties::DEVICE] == "QtBot");
    QVERIFY(serializedIdentify[Identify::COMPRESS] == true);
    QVERIFY(serializedIdentify[Identify::LARGE_THRESHOLD] == TEST_INT1);
    QVERIFY(serializedIdentify[Identify::SHARD].toArray()[0] == TEST_INT2);
    QVERIFY(serializedIdentify[Identify::SHARD].toArray()[1] == TEST_INT1);
    QVERIFY(serializedIdentify[Identify::PRESENCE].toObject()[presence.SINCE] == TEST_INT1);
    QVERIFY(serializedIdentify[Identify::GUILD_SUBSCRIPTIONS] == true);
    QVERIFY(serializedIdentify[Identify::INTENTS] == TEST_INT2);
}

void
IdentifyTest::test_serialization_minimal() {
    Identify identify;

    identify.setToken(TEST_STRING1);

    IdentifyProperties properties(PLD_PROPERTIES);

    identify.setProperties(properties.toQJsonObject());

    QJsonObject serializedIdentify = identify.toQJsonObject();

    QVERIFY(serializedIdentify[Identify::TOKEN] == TEST_STRING1);
    QVERIFY(serializedIdentify[Identify::PROPERTIES].toObject()[IdentifyProperties::DEVICE] == "QtBot");
    QVERIFY(!serializedIdentify.contains(Identify::COMPRESS));
    QVERIFY(!serializedIdentify.contains(Identify::LARGE_THRESHOLD));
    QVERIFY(!serializedIdentify.contains(Identify::SHARD));
    QVERIFY(!serializedIdentify.contains(Identify::PRESENCE));
    QVERIFY(!serializedIdentify.contains(Identify::GUILD_SUBSCRIPTIONS));
    QVERIFY(!serializedIdentify.contains(Identify::INTENTS));
}

static IdentifyTest IDENTIFY_TEST;
