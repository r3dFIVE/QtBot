#include "tst_guildmemeber.h"

#include <payloads/guildmember.h>


void
GuildMemberTest::test_deserialization_full() {
    GuildMember guildMember;
    guildMember.fromQString(PLD_GUILD_MEMBER_FULL);

    QVERIFY(guildMember.user);
    QVERIFY(guildMember.nick == TEST_STRING1);

    User user;
    user.fromQJsonObject(guildMember.user->toQJsonObject());

    QVERIFY(user.username == TEST_STRING1);
    QVERIFY(guildMember.roles.size() == 2);
    QVERIFY(guildMember.roles[0] == TEST_STRING2);
    QVERIFY(guildMember.roles[1] == TEST_STRING1);
    QVERIFY(guildMember.joined_at == TEST_STRING2);
    QVERIFY(guildMember.deaf == true);
    QVERIFY(guildMember.mute == true);
    QVERIFY(guildMember.premium_since == TEST_STRING1);
}

void
GuildMemberTest::test_deserialization_minimal() {
    GuildMember guildMember;
    guildMember.fromQString(PLD_GUILD_MEMBER_MINIMAL);

    QVERIFY(guildMember.nick == TEST_STRING1);
    QVERIFY(!guildMember.user);
    QVERIFY(guildMember.roles.size() == 2);
    QVERIFY(guildMember.roles[0] == TEST_STRING2);
    QVERIFY(guildMember.roles[1] == TEST_STRING1);
    QVERIFY(guildMember.joined_at == TEST_STRING2);
    QVERIFY(guildMember.deaf == true);
    QVERIFY(guildMember.mute == true);
    QVERIFY(guildMember.premium_since == "");
}

void
GuildMemberTest::test_serialization_full() {
    GuildMember guildMember;
    guildMember.setNick(TEST_STRING1);

    User user;
    user.fromQString(PLD_USER_MINIMAL);
    guildMember.setUser(user.toQJsonObject());

    QJsonArray roles = { TEST_STRING2, TEST_STRING1 };
    guildMember.setRoles(roles);

    guildMember.setJoinedAt(TEST_STRING2);
    guildMember.setDeaf(true);
    guildMember.setMute(true);
    guildMember.setPremiumSince(TEST_STRING1);

    QJsonObject serializedGuildMember = guildMember.toQJsonObject();

    QVERIFY(serializedGuildMember.contains(guildMember.USER));
    user.fromQJsonObject(serializedGuildMember[guildMember.USER].toObject());
    QVERIFY(user.username == TEST_STRING1);
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
    GuildMember guildMember;
    guildMember.setNick(TEST_STRING1);

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

