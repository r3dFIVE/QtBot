/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
