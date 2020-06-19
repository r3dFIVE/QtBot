#include "tst_activityemoji.h"

#include <payloads/activityemoji.h>
#include <payloads/testpayloads.h>

void
ActivityEmojiTest::test_serialization_minimal() {
    ActivityEmoji emoji;
    emoji.name = TEST_STRING1;

    QJsonObject serialized = emoji.toQJsonObject();

    QVERIFY(serialized[emoji.NAME] == TEST_STRING1);
    QVERIFY(serialized[emoji.NAME] != TEST_STRING2);

    QVERIFY(!serialized.contains(emoji.ID));

    QVERIFY(!serialized.contains(emoji.ANIMATED));
}

void
ActivityEmojiTest::test_serialization_full() {
    ActivityEmoji emoji;
    emoji.name = TEST_STRING1;
    emoji.id = TEST_STRING2;
    emoji.animated = QSharedPointer<bool>(new bool(true));

    QJsonObject serialized = emoji.toQJsonObject();

    QVERIFY(serialized[emoji.NAME] == TEST_STRING1);
    QVERIFY(serialized[emoji.NAME] != TEST_STRING2);

    QVERIFY(serialized[emoji.ID] == TEST_STRING2);

    QVERIFY(serialized.contains(emoji.ANIMATED));
    QVERIFY(serialized[emoji.ANIMATED].toBool() == true);
}

void
ActivityEmojiTest::test_deserialization_minimal() {
    ActivityEmoji emoji;
    emoji.fromQString(PLD_EMOJI_MINIMAL);

    QVERIFY(emoji.name == TEST_STRING1);
    QVERIFY(emoji.name != TEST_STRING2);

    QVERIFY(emoji.id == "");

    QVERIFY(emoji.animated == nullptr);
}

void
ActivityEmojiTest::test_deserialization_full() {
    ActivityEmoji emoji;
    QString s = PLD_EMOJI_FULL;
    emoji.fromQString(PLD_EMOJI_FULL);

    QVERIFY(emoji.name == TEST_STRING1);
    QVERIFY(emoji.name != TEST_STRING2);

    QVERIFY(emoji.id != TEST_STRING1);
    QVERIFY(emoji.id == TEST_STRING2);

    QVERIFY(emoji.animated != nullptr);
    QVERIFY(emoji.animated);
}

static ActivityEmojiTest ACTIVITY_EMOJI_TEST;
