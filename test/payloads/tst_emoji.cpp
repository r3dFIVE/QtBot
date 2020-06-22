#include "tst_emoji.h"

#include <payloads/emoji.h>


void
EmojiTest::test_serialization_minimal() {
    Emoji emoji;
    emoji.id = TEST_STRING1;
    emoji.name = TEST_STRING2;

    QJsonObject serializedEmoji = emoji.toQJsonObject();

    QVERIFY(serializedEmoji[emoji.ID] == TEST_STRING1);

    QVERIFY(serializedEmoji[emoji.NAME] == TEST_STRING2);

    QVERIFY(!serializedEmoji.contains(emoji.ROLES));

    QVERIFY(!serializedEmoji.contains(emoji.USER));

    QVERIFY(!serializedEmoji.contains(emoji.REQUIRE_COLONS));

    QVERIFY(!serializedEmoji.contains(emoji.MANAGED));

    QVERIFY(!serializedEmoji.contains(emoji.ANIMATED));

    QVERIFY(!serializedEmoji.contains(emoji.AVAILABLE));
}

void
EmojiTest::test_serialization_full() {
    Emoji emoji;
    emoji.id = TEST_STRING1;
    emoji.name = TEST_STRING2;
    emoji.roles = QList<QString> { TEST_STRING1, TEST_STRING2 };

    User user;
    user.username = TEST_STRING1;
    emoji.setUser(user.toQJsonObject());

    emoji.setRequireColons(QJsonValue(true));
    emoji.setManaged(QJsonValue(true));
    emoji.setAnimated(QJsonValue(true));
    emoji.setAvailable(QJsonValue(true));

    QJsonObject serializedEmoji = emoji.toQJsonObject();

    QVERIFY(serializedEmoji[emoji.ID] == TEST_STRING1);

    QVERIFY(serializedEmoji[emoji.NAME] == TEST_STRING2);

    QVERIFY(serializedEmoji.contains(emoji.ROLES));
    QJsonArray arr = serializedEmoji[emoji.ROLES].toArray();
    QVERIFY(arr[0] == TEST_STRING1);
    QVERIFY(arr[1] == TEST_STRING2);

    QVERIFY(serializedEmoji.contains(emoji.USER));
    QJsonObject jsonUser = serializedEmoji[emoji.USER].toObject();
    QVERIFY(jsonUser.contains(user.USERNAME));
    QVERIFY(jsonUser[user.USERNAME] == TEST_STRING1);


    QVERIFY(serializedEmoji.contains(emoji.REQUIRE_COLONS));
    QVERIFY(serializedEmoji[emoji.REQUIRE_COLONS] == true);

    QVERIFY(serializedEmoji.contains(emoji.MANAGED));
    QVERIFY(serializedEmoji[emoji.MANAGED] == true);

    QVERIFY(serializedEmoji.contains(emoji.ANIMATED));
    QVERIFY(serializedEmoji[emoji.ANIMATED] == true);

    QVERIFY(serializedEmoji.contains(emoji.AVAILABLE));
    QVERIFY(serializedEmoji[emoji.AVAILABLE] == true);
}

void
EmojiTest::test_deserialization_minimal() {
    Emoji emoji;
    emoji.fromQString(PLD_EMOJI_MINIMAL);

    QVERIFY(emoji.id == TEST_STRING1);

    QVERIFY(emoji.name == TEST_STRING2);

    QVERIFY(emoji.roles.size() == 0);

    QVERIFY(emoji.user == nullptr);

    QVERIFY(emoji.require_colons == nullptr);

    QVERIFY(emoji.managed == nullptr);

    QVERIFY(emoji.animated == nullptr);

    QVERIFY(emoji.available == nullptr);
}

void
EmojiTest::test_deserialization_full() {
    Emoji emoji;
    emoji.fromQString(PLD_EMOJI_FULL);

    QVERIFY(emoji.id == TEST_STRING1);
    QVERIFY(emoji.name == TEST_STRING2);

    QVERIFY(emoji.roles.size() == 2);
    QVERIFY(emoji.roles[0] == TEST_STRING1);
    QVERIFY(emoji.roles[1] == TEST_STRING2);

    QVERIFY(emoji.user != nullptr);
    QVERIFY(emoji.user->username == TEST_STRING2);

    QVERIFY(emoji.require_colons != nullptr);
    QVERIFY(*emoji.require_colons == true);

    QVERIFY(emoji.managed != nullptr);
    QVERIFY(*emoji.managed == true);

    QVERIFY(emoji.animated != nullptr);
    QVERIFY(*emoji.animated == true);

    QVERIFY(emoji.available != nullptr);
    QVERIFY(*emoji.available == true);
}

static EmojiTest EMOJI_TEST;
