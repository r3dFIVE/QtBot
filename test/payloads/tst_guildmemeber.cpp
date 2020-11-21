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

#include "tst_guildmemeber.h"

#include "payloads/guildmember.h"
#include "payloads/user.h"


void
GuildMemberTest::test_deserialization_full() {
    GuildMember guildMember;

    guildMember.fromQString(PLD_GUILD_MEMBER_FULL);

    QVERIFY(!guildMember.getUser().isEmpty());
    QVERIFY(guildMember.getNick() == TEST_STRING1);

    User user(guildMember.getUser());

    QVERIFY(user.getUsername() == TEST_STRING1);
    QVERIFY(guildMember.getRoles().size() == 2);
    QVERIFY(guildMember.getRoles()[0] == TEST_STRING2);
    QVERIFY(guildMember.getRoles()[1] == TEST_STRING1);
    QVERIFY(guildMember.getJoinedAt() == TEST_STRING2);
    QVERIFY(guildMember.getDeaf() == true);
    QVERIFY(guildMember.getMute() == true);
    QVERIFY(guildMember.getPremiumSince() == TEST_STRING1);
}

void
GuildMemberTest::test_deserialization_minimal() {
    GuildMember guildMember(PLD_GUILD_MEMBER_MINIMAL);

    QVERIFY(guildMember.getNick() == TEST_STRING1);
    QVERIFY(guildMember.getUser().isEmpty());
    QVERIFY(guildMember.getRoles().size() == 2);
    QVERIFY(guildMember.getRoles()[0] == TEST_STRING2);
    QVERIFY(guildMember.getRoles()[1] == TEST_STRING1);
    QVERIFY(guildMember.getJoinedAt() == TEST_STRING2);
    QVERIFY(guildMember.getDeaf() == true);
    QVERIFY(guildMember.getMute() == true);
    QVERIFY(guildMember.getPremiumSince() == "");
}

void
GuildMemberTest::test_serialization_full() {
    GuildMember guildMember(TEST_STRING1);

    User user(PLD_USER_MINIMAL);

    guildMember.setUser(user.toQJsonObject());

    QJsonArray roles = { TEST_STRING2, TEST_STRING1 };

    guildMember.setRoles(roles);

    guildMember.setJoinedAt(TEST_STRING2);

    guildMember.setDeaf(true);

    guildMember.setMute(true);

    guildMember.setPremiumSince(TEST_STRING1);

    QJsonObject serializedGuildMember = guildMember.toQJsonObject();

    QVERIFY(serializedGuildMember.contains(guildMember.USER));

    user.setQJsonObject(serializedGuildMember[guildMember.USER].toObject());

    QVERIFY(user.getUsername() == TEST_STRING1);
    QVERIFY(serializedGuildMember[guildMember.NICK] == TEST_STRING1);
    QVERIFY(serializedGuildMember.contains(guildMember.ROLES));

    roles = serializedGuildMember[guildMember.ROLES].toArray();

    QVERIFY(roles[0] == TEST_STRING2);
    QVERIFY(roles[1] == TEST_STRING1);
    QVERIFY(serializedGuildMember[guildMember.JOINED_AT] == TEST_STRING2);
    QVERIFY(serializedGuildMember[guildMember.DEAF] == true);
    QVERIFY(serializedGuildMember[guildMember.MUTE] == true);
}

void
GuildMemberTest::test_serialization_minimal() {
    GuildMember guildMember(TEST_STRING1);

    QJsonArray roles = { TEST_STRING2, TEST_STRING1 };

    guildMember.setRoles(roles);

    guildMember.setJoinedAt(TEST_STRING2);

    guildMember.setDeaf(true);

    guildMember.setMute(true);

    QJsonObject serializedGuildMember = guildMember.toQJsonObject();

    QVERIFY(!serializedGuildMember.contains(guildMember.USER));
    QVERIFY(serializedGuildMember[guildMember.NICK] == TEST_STRING1);
    QVERIFY(serializedGuildMember.contains(guildMember.ROLES));

    roles = serializedGuildMember[guildMember.ROLES].toArray();

    QVERIFY(roles[0] == TEST_STRING2);
    QVERIFY(roles[1] == TEST_STRING1);
    QVERIFY(serializedGuildMember[guildMember.JOINED_AT] == TEST_STRING2);
    QVERIFY(serializedGuildMember[guildMember.DEAF] == true);
    QVERIFY(serializedGuildMember[guildMember.MUTE] == true);
}

