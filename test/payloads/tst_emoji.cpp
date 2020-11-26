/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "tst_emoji.h"

#include "payloads/emoji.h"
#include "payloads/user.h"


void
EmojiTest::test_serialization_minimal() {
    Emoji emoji;

    emoji.setId(TEST_STRING1);

    emoji.setName(TEST_STRING2);

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

    emoji.setId(TEST_STRING1);

    emoji.setName(TEST_STRING2);

    QJsonArray roles = { TEST_STRING1, TEST_STRING2 };

    emoji.setRoles(roles);

    User user;

    user.setUsername(TEST_STRING1);

    emoji.setUser(user.toQJsonObject());

    emoji.setRequireColons(true);

    emoji.setManaged(true);

    emoji.setAnimated(true);

    emoji.setAvailable(true);

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

    QVERIFY(emoji.getId() == TEST_STRING1);
    QVERIFY(emoji.getName() == TEST_STRING2);
    QVERIFY(emoji.getRoles().size() == 0);
    QVERIFY(emoji.getUser().isEmpty());
    QVERIFY(emoji.getRequireColons().isUndefined());
    QVERIFY(emoji.getManaged().isUndefined());
    QVERIFY(emoji.getAnimated().isUndefined());
    QVERIFY(emoji.getAvailable().isUndefined());
}

void
EmojiTest::test_deserialization_full() {
    Emoji emoji(PLD_EMOJI_FULL);

    QVERIFY(emoji.getId() == TEST_STRING1);
    QVERIFY(emoji.getName() == TEST_STRING2);
    QVERIFY(emoji.getRoles().size() == 2);
    QVERIFY(emoji.getRoles()[0] == TEST_STRING1);
    QVERIFY(emoji.getRoles()[1] == TEST_STRING2);
    QVERIFY(emoji.getUser()[User::USERNAME] == TEST_STRING2);
    QVERIFY(emoji.getRequireColons() == true);
    QVERIFY(emoji.getManaged() == true);
    QVERIFY(emoji.getAnimated() == true);
    QVERIFY(emoji.getAvailable() == true);
}

static EmojiTest EMOJI_TEST;
