#include "tst_activityemoji.h"

#include "payloads/activityemoji.h"

void
ActivityEmojiTest::test_serialization_minimal() {
    ActivityEmoji emoji;

    emoji.setName(TEST_STRING1);

    QJsonObject serialized = emoji.toQJsonObject();

    QVERIFY(serialized[emoji.NAME] == TEST_STRING1);
    QVERIFY(serialized[emoji.NAME] != TEST_STRING2);
    QVERIFY(!serialized.contains(emoji.ID));
    QVERIFY(!serialized.contains(emoji.ANIMATED));
}

void
ActivityEmojiTest::test_serialization_full() {
    ActivityEmoji emoji;

    emoji.setName(TEST_STRING1);

    emoji.setId(TEST_STRING2);

    emoji.setAnimated(true);

    QJsonObject serialized = emoji.toQJsonObject();

    QVERIFY(serialized[emoji.NAME] == TEST_STRING1);
    QVERIFY(serialized[emoji.NAME] != TEST_STRING2);
    QVERIFY(serialized[emoji.ID] == TEST_STRING2);
    QVERIFY(serialized.contains(emoji.ANIMATED));
    QVERIFY(serialized[emoji.ANIMATED].toBool() == true);
}

void
ActivityEmojiTest::test_deserialization_minimal() {
    ActivityEmoji emoji(PLD_ACTIVITY_EMOJI_MINIMAL);

    QVERIFY(emoji.getName() == TEST_STRING1);
    QVERIFY(emoji.getName() != TEST_STRING2);
    QVERIFY(emoji.getId().isUndefined());
    QVERIFY(emoji.getAnimated().isUndefined());
}

void
ActivityEmojiTest::test_deserialization_full() {
    ActivityEmoji emoji(PLD_ACTIVITY_EMOJI_FULL);

    QVERIFY(emoji.getName() == TEST_STRING1);
    QVERIFY(emoji.getName() != TEST_STRING2);
    QVERIFY(emoji.getId() != TEST_STRING1);
    QVERIFY(emoji.getId() == TEST_STRING2);
    QVERIFY(emoji.getAnimated().toBool());
}

static ActivityEmojiTest ACTIVITY_EMOJI_TEST;
