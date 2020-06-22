#include "tst_voicestate.h"

#include <payloads/voicestate.h>


void
VoiceStateTest::test_deserialization_full() {
    VoiceState voiceState;
    voiceState.fromQString(PLD_VOICE_STATE_FULL);

    QVERIFY(voiceState.guild_id == TEST_STRING2);
    QVERIFY(voiceState.channel_id == TEST_STRING1);
    QVERIFY(voiceState.user_id == TEST_STRING2);
    QVERIFY(voiceState.member);

    GuildMember member;
    member.fromQJsonObject(voiceState.member->toQJsonObject());

    QVERIFY(member.nick == TEST_STRING1);
    QVERIFY(voiceState.session_id == TEST_STRING1);
    QVERIFY(voiceState.deaf == true);
    QVERIFY(voiceState.mute == true);
    QVERIFY(voiceState.self_deaf == true);
    QVERIFY(voiceState.self_mute == true);
    QVERIFY(voiceState.self_stream);
    QVERIFY(*voiceState.self_stream == true);
    QVERIFY(voiceState.suppress == true);
}

void
VoiceStateTest::test_deserialization_minimal() {
    VoiceState voiceState;
    voiceState.fromQString(PLD_VOICE_STATE_MINIMAL);

    QVERIFY(voiceState.guild_id == "");
    QVERIFY(voiceState.channel_id == TEST_STRING1);
    QVERIFY(voiceState.user_id == TEST_STRING2);
    QVERIFY(!voiceState.member);
    QVERIFY(voiceState.session_id == TEST_STRING1);
    QVERIFY(voiceState.deaf == true);
    QVERIFY(voiceState.mute == true);
    QVERIFY(voiceState.self_deaf == true);
    QVERIFY(voiceState.self_mute == true);
    QVERIFY(!voiceState.self_stream);
    QVERIFY(voiceState.suppress == true);
}

void
VoiceStateTest::test_serialization_full() {
    VoiceState voiceState;
    voiceState.setGuildId(TEST_STRING1);
    voiceState.setChannelId(TEST_STRING2);
    voiceState.setUserId(TEST_STRING1);

    GuildMember guildMember;
    guildMember.fromQString(PLD_GUILD_MEMBER_MINIMAL);

    voiceState.setMember(guildMember.toQJsonObject());
    voiceState.setSessionId(TEST_STRING2);
    voiceState.setDeaf(true);
    voiceState.setMute(true);
    voiceState.setSelfDeaf(true);
    voiceState.setSelfMute(true);
    voiceState.setSelfStream(true);
    voiceState.setSuppress(true);

    QJsonObject serializedVoiceState = voiceState.toQJsonObject();

    QVERIFY(serializedVoiceState[voiceState.GUILD_ID] == TEST_STRING1);
    QVERIFY(serializedVoiceState[voiceState.CHANNEL_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[voiceState.USER_ID] == TEST_STRING1);

    QVERIFY(!serializedVoiceState.contains(voiceState.MEMBER));
    guildMember.fromQJsonObject(serializedVoiceState[voiceState.MEMBER].toObject());
    QVERIFY(guildMember.getNick() == TEST_STRING1);
    QVERIFY(serializedVoiceState[voiceState.SESSION_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[voiceState.DEAF] == true);
    QVERIFY(serializedVoiceState[voiceState.MUTE] == true);
    QVERIFY(serializedVoiceState[voiceState.SELF_DEAF] == true);
    QVERIFY(serializedVoiceState[voiceState.SELF_MUTE] == true);
    QVERIFY(serializedVoiceState[voiceState.SELF_STREAM] == true);
    QVERIFY(serializedVoiceState[voiceState.SUPPRESS] == true);
}

void
VoiceStateTest::test_serialization_minimal() {
    VoiceState voiceState;
    voiceState.setChannelId(TEST_STRING2);
    voiceState.setUserId(TEST_STRING1);
    voiceState.setSessionId(TEST_STRING2);
    voiceState.setDeaf(true);
    voiceState.setMute(true);
    voiceState.setSelfDeaf(true);
    voiceState.setSelfMute(true);
    voiceState.setSuppress(true);

    QJsonObject serializedVoiceState = voiceState.toQJsonObject();

    QVERIFY(!serializedVoiceState.contains(voiceState.GUILD_ID));
    QVERIFY(serializedVoiceState[voiceState.CHANNEL_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[voiceState.USER_ID] == TEST_STRING1);
    QVERIFY(!serializedVoiceState.contains(voiceState.MEMBER));
    QVERIFY(serializedVoiceState[voiceState.SESSION_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[voiceState.DEAF] == true);
    QVERIFY(serializedVoiceState[voiceState.MUTE] == true);
    QVERIFY(serializedVoiceState[voiceState.SELF_DEAF] == true);
    QVERIFY(serializedVoiceState[voiceState.SELF_MUTE] == true);
    QVERIFY(!serializedVoiceState.contains(voiceState.SELF_STREAM));
    QVERIFY(serializedVoiceState[voiceState.SUPPRESS] == true);
}

static VoiceStateTest VOICE_STATE_TEST;
