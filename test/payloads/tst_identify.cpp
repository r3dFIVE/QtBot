#include "tst_identify.h"

#include <payloads/identify.h>


void
IdentifyTest::test_deserialization_full() {
    Identify identify;
    identify.fromQString(PLD_IDENTIFY_FULL);

    QVERIFY(identify.getToken() == TEST_STRING1);
    QVERIFY(identify.properties);
    IdentifyProperties properties;
    properties.fromQJsonObject(identify.getProperties());
    QVERIFY(identify.compress);
    QVERIFY(identify.getCompress() == true);
    QVERIFY(identify.large_threshold);
    QVERIFY(identify.getLargeThreshold() == TEST_INT1);
    QVERIFY(identify.shard[0]);
    QVERIFY(*identify.shard[0] == TEST_INT2);
    QVERIFY(identify.shard[1]);
    QVERIFY(*identify.shard[1] == TEST_INT1);
    QVERIFY(identify.presence);
    UpdateStatus presence;
    presence.fromQJsonObject(identify.getPresence());
    QVERIFY(presence.getSince() == TEST_INT1);
    QVERIFY(identify.guild_subscriptions);
    QVERIFY(identify.getGuildSubscriptions() == true);
    QVERIFY(identify.intents);
    QVERIFY(identify.getIntents() == TEST_INT2);
}

void
IdentifyTest::test_deserialization_minimal() {
    Identify identify;
    identify.fromQString(PLD_IDENTIFY_MINIMAL);

    QVERIFY(identify.getToken() == TEST_STRING1);
    QVERIFY(identify.properties);
    IdentifyProperties properties;
    properties.fromQJsonObject(identify.getProperties());
    QVERIFY(properties.$browser == "QtBot");
    QVERIFY(!identify.compress);
    QVERIFY(!identify.large_threshold);
    QVERIFY(!identify.shard[0]);
    QVERIFY(!identify.shard[1]);
    QVERIFY(!identify.presence);
    QVERIFY(!identify.guild_subscriptions);
    QVERIFY(!identify.intents);
}

void
IdentifyTest::test_serialization_full() {
    Identify identify;
    identify.setToken(TEST_STRING1);
    IdentifyProperties properties;
    properties.fromQString(PLD_PROPERTIES);
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

    QVERIFY(serializedIdentify[identify.TOKEN] == TEST_STRING1);
    QVERIFY(serializedIdentify.contains(identify.PROPERTIES));
    QVERIFY(serializedIdentify[identify.PROPERTIES].toObject()[properties.DEVICE] == "QtBot");
    QVERIFY(serializedIdentify[identify.COMPRESS] == true);
    QVERIFY(serializedIdentify[identify.LARGE_THRESHOLD] == TEST_INT1);
    QVERIFY(serializedIdentify[identify.SHARD].toArray()[0] == TEST_INT2);
    QVERIFY(serializedIdentify[identify.SHARD].toArray()[1] == TEST_INT1);
    QVERIFY(serializedIdentify[identify.PRESENCE].toObject()[presence.SINCE] == TEST_INT1);
    QVERIFY(serializedIdentify[identify.GUILD_SUBSCRIPTIONS] == true);
    QVERIFY(serializedIdentify[identify.INTENTS] == TEST_INT2);
}

void
IdentifyTest::test_serialization_minimal() {
    Identify identify;
    identify.setToken(TEST_STRING1);
    IdentifyProperties properties;
    properties.fromQString(PLD_PROPERTIES);
    identify.setProperties(properties.toQJsonObject());

    QJsonObject serializedIdentify = identify.toQJsonObject();

    QVERIFY(serializedIdentify[identify.TOKEN] == TEST_STRING1);
    QVERIFY(serializedIdentify.contains(identify.PROPERTIES));
    QVERIFY(serializedIdentify[identify.PROPERTIES].toObject()[properties.DEVICE] == "QtBot");
    QVERIFY(!serializedIdentify.contains(identify.COMPRESS));
    QVERIFY(!serializedIdentify.contains(identify.LARGE_THRESHOLD));
    QVERIFY(!serializedIdentify.contains(identify.SHARD));
    QVERIFY(!serializedIdentify.contains(identify.PRESENCE));
    QVERIFY(!serializedIdentify.contains(identify.GUILD_SUBSCRIPTIONS));
    QVERIFY(!serializedIdentify.contains(identify.INTENTS));
}

static IdentifyTest IDENTIFY_TEST;
