#include "tst_channel.h"

#include <payloads/channel.h>


void
ChannelTest::test_deserialization_full() {
    Channel channel;
    qDebug() << PLD_CHANNEL_FULL;
    channel.fromQString(PLD_CHANNEL_FULL);

    QVERIFY(channel.getId() == TEST_STRING1);
    QVERIFY(channel.getType() == TEST_INT1);
    QVERIFY(channel.getGuildId() == TEST_STRING2);
    QVERIFY(channel.getPosition() == TEST_INT2);
    QVERIFY(channel.getPermissionOverwrites().size() == 1);
    QVERIFY(channel.permission_overwrites[0].getId() == TEST_STRING1);
    QVERIFY(channel.getName() == TEST_STRING1);
    QVERIFY(channel.getTopic() == TEST_STRING2);
    QVERIFY(channel.getNsfw() == true);
    QVERIFY(channel.getLastMessageId() == TEST_STRING1);
    QVERIFY(channel.getBitrate() == TEST_INT1);
    QVERIFY(channel.getUserLimit() == TEST_INT2);
    QVERIFY(channel.getRateLimitPerUser() == TEST_INT1);
    QVERIFY(channel.getRecipients().size() == 1);
    QVERIFY(channel.recipients[0].getUsername() == TEST_STRING2);
    QVERIFY(channel.getIcon() == TEST_STRING2);
    QVERIFY(channel.getOwnerId() == TEST_STRING1);
    QVERIFY(channel.getApplicationId() == TEST_STRING2);
    QVERIFY(channel.getParentId() == TEST_STRING1);
    QVERIFY(channel.getLastPinTimestamp() == TEST_STRING2);
}

void
ChannelTest::test_deserialization_minimal() {
    Channel channel;
    qDebug() << PLD_CHANNEL_MINIMAL;
    channel.fromQString(PLD_CHANNEL_MINIMAL);

    QVERIFY(channel.getId() == TEST_STRING1);
    QVERIFY(channel.getType() == TEST_INT1);
    QVERIFY(channel.getGuildId().isEmpty());
    QVERIFY(channel.getPosition() == QJsonValue::Null);
    QVERIFY(channel.permission_overwrites.size() == 0);
    QVERIFY(channel.getName().isEmpty());
    QVERIFY(channel.getTopic().isEmpty());
    QVERIFY(channel.getNsfw() == QJsonValue::Null);
    QVERIFY(channel.getLastMessageId().isEmpty());
    QVERIFY(channel.getBitrate() == QJsonValue::Null);
    QVERIFY(channel.getUserLimit() == QJsonValue::Null);
    QVERIFY(channel.getRateLimitPerUser() == QJsonValue::Null);
    QVERIFY(channel.getRecipients().size() == 0);
    QVERIFY(channel.getIcon().isEmpty());
    QVERIFY(channel.getOwnerId().isEmpty());
    QVERIFY(channel.getApplicationId().isEmpty());
    QVERIFY(channel.getParentId().isEmpty());
    QVERIFY(channel.getLastPinTimestamp().isEmpty());
}

void
ChannelTest::test_serialization_full() {
    Channel channel;
    channel.setId(TEST_STRING1);
    channel.setType(TEST_INT1);
    channel.setGuildId(TEST_STRING2);
    channel.setPosition(TEST_INT2);
    PermissionOverwrite permissionOverwrite;
    permissionOverwrite.fromQString(PLD_PERMISSION_OVERWRITE);
    QJsonArray permissionOverwrites = { permissionOverwrite.toQJsonObject() };
    channel.setPermissionOverwrites(permissionOverwrites);
    channel.setName(TEST_STRING1);
    channel.setTopic(TEST_STRING2);
    channel.setNsfw(true);
    channel.setLastMessageId(TEST_STRING1);
    channel.setBitrate(TEST_INT1);
    channel.setUserLimit(TEST_INT2);
    channel.setRateLimitPerUser(TEST_INT1);
    User user;
    user.fromQString(PLD_USER_MINIMAL);
    QJsonArray recipients = { user.toQJsonObject() };
    channel.setRecipients(recipients);
    channel.setIcon(TEST_STRING2);
    channel.setOwnerId(TEST_STRING1);
    channel.setApplicationId(TEST_STRING2);
    channel.setParentId(TEST_STRING1);
    channel.setLastPinTimestamp(TEST_STRING2);

    QJsonObject serializedChannel = channel.toQJsonObject();

    QVERIFY(serializedChannel[channel.ID] == TEST_STRING1);
    QVERIFY(serializedChannel[channel.TYPE] == TEST_INT1);
    QVERIFY(serializedChannel[channel.GUILD_ID] == TEST_STRING2);
    QVERIFY(serializedChannel[channel.POSITION] == TEST_INT2);
    QVERIFY(serializedChannel[channel.PERMISSION_OVERWRITES].toArray().at(0)[permissionOverwrite.ID].toString() == TEST_STRING1);
    QVERIFY(serializedChannel[channel.NAME] == TEST_STRING1);
    QVERIFY(serializedChannel[channel.TOPIC] == TEST_STRING2);
    QVERIFY(serializedChannel[channel.NSFW] == true);
    QVERIFY(serializedChannel[channel.LAST_MESSAGE_ID] == TEST_STRING1);
    QVERIFY(serializedChannel[channel.BITRATE] == TEST_INT1);
    QVERIFY(serializedChannel[channel.USER_LIMIT] == TEST_INT2);
    QVERIFY(serializedChannel[channel.RATE_LIMIT_PER_USER] == TEST_INT1);
    QVERIFY(serializedChannel[channel.RECIPIENTS].toArray().at(0)[user.ID] == TEST_STRING1);
    QVERIFY(serializedChannel[channel.ICON] == TEST_STRING2);
    QVERIFY(serializedChannel[channel.OWNER_ID] == TEST_STRING1);
    QVERIFY(serializedChannel[channel.APPLICATION_ID] == TEST_STRING2);
    QVERIFY(serializedChannel[channel.PARENT_ID] == TEST_STRING1);
    QVERIFY(serializedChannel[channel.LAST_PIN_TIMESTAMP] == TEST_STRING2);
}

void
ChannelTest::test_serialization_minimal() {
    Channel channel;
    channel.setId(TEST_STRING1);
    channel.setType(TEST_INT1);

    QJsonObject serializedChannel = channel.toQJsonObject();

    QVERIFY(serializedChannel[channel.ID] == TEST_STRING1);
    QVERIFY(serializedChannel[channel.TYPE] == TEST_INT1);
    QVERIFY(!serializedChannel.contains(channel.GUILD_ID));
    QVERIFY(!serializedChannel.contains(channel.POSITION));
    QVERIFY(!serializedChannel.contains(channel.PERMISSION_OVERWRITES));
    QVERIFY(!serializedChannel.contains(channel.NAME));
    QVERIFY(!serializedChannel.contains(channel.TOPIC));
    QVERIFY(!serializedChannel.contains(channel.NSFW));
    QVERIFY(!serializedChannel.contains(channel.LAST_MESSAGE_ID));
    QVERIFY(!serializedChannel.contains(channel.BITRATE));
    QVERIFY(!serializedChannel.contains(channel.USER_LIMIT));
    QVERIFY(!serializedChannel.contains(channel.RATE_LIMIT_PER_USER));
    QVERIFY(!serializedChannel.contains(channel.RECIPIENTS));
    QVERIFY(!serializedChannel.contains(channel.ICON));
    QVERIFY(!serializedChannel.contains(channel.OWNER_ID));
    QVERIFY(!serializedChannel.contains(channel.APPLICATION_ID));
    QVERIFY(!serializedChannel.contains(channel.PARENT_ID));
    QVERIFY(!serializedChannel.contains(channel.LAST_PIN_TIMESTAMP));
}

static ChannelTest CHANNEL_TEST;
