#include "tst_voicestate.h"

#include "payloads/voicestate.h"
#include "payloads/guildmember.h"


void
VoiceStateTest::test_deserialization_full() {
    VoiceState voiceState(PLD_VOICE_STATE_FULL);

    QVERIFY(voiceState.getGuildId() == TEST_STRING2);
    QVERIFY(voiceState.getChannelId() == TEST_STRING1);
    QVERIFY(voiceState.getUserId() == TEST_STRING2);

    GuildMember member(voiceState.getMember());

    QVERIFY(member.getNick() == TEST_STRING1);
    QVERIFY(voiceState.getSessionId() == TEST_STRING1);
    QVERIFY(voiceState.getDeaf() == true);
    QVERIFY(voiceState.getMute() == true);
    QVERIFY(voiceState.getSelfDeaf() == true);
    QVERIFY(voiceState.getSelfMute() == true);
    QVERIFY(voiceState.getSelfStream() == true);
    QVERIFY(voiceState.getSuppress() == true);
}

void
VoiceStateTest::test_deserialization_minimal() {
    VoiceState voiceState(PLD_VOICE_STATE_MINIMAL);

    QVERIFY(voiceState.getGuildId().isUndefined());
    QVERIFY(voiceState.getChannelId() == TEST_STRING1);
    QVERIFY(voiceState.getUserId() == TEST_STRING2);
    QVERIFY(voiceState.getMember().isEmpty());
    QVERIFY(voiceState.getSessionId() == TEST_STRING1);
    QVERIFY(voiceState.getDeaf() == true);
    QVERIFY(voiceState.getMute() == true);
    QVERIFY(voiceState.getSelfDeaf() == true);
    QVERIFY(voiceState.getSelfMute() == true);
    QVERIFY(voiceState.getSelfStream().isUndefined());
    QVERIFY(voiceState.getSuppress() == true);
}

void
VoiceStateTest::test_serialization_full() {
    VoiceState voiceState;

    voiceState.setGuildId(TEST_STRING1);

    voiceState.setChannelId(TEST_STRING2);

    voiceState.setUserId(TEST_STRING1);

    GuildMember guildMember(PLD_GUILD_MEMBER_MINIMAL);

    voiceState.setMember(guildMember.toQJsonObject());

    voiceState.setSessionId(TEST_STRING2);

    voiceState.setDeaf(true);

    voiceState.setMute(true);

    voiceState.setSelfDeaf(true);

    voiceState.setSelfMute(true);

    voiceState.setSelfStream(true);

    voiceState.setSuppress(true);

    QJsonObject serializedVoiceState = voiceState.toQJsonObject();

    QVERIFY(serializedVoiceState[VoiceState::GUILD_ID] == TEST_STRING1);
    QVERIFY(serializedVoiceState[VoiceState::CHANNEL_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[VoiceState::USER_ID] == TEST_STRING1);

    guildMember.setQJsonObject(serializedVoiceState[VoiceState::MEMBER].toObject());

    QVERIFY(guildMember.getNick() == TEST_STRING1);
    QVERIFY(serializedVoiceState[VoiceState::SESSION_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[VoiceState::DEAF] == true);
    QVERIFY(serializedVoiceState[VoiceState::MUTE] == true);
    QVERIFY(serializedVoiceState[VoiceState::SELF_DEAF] == true);
    QVERIFY(serializedVoiceState[VoiceState::SELF_MUTE] == true);
    QVERIFY(serializedVoiceState[VoiceState::SELF_STREAM] == true);
    QVERIFY(serializedVoiceState[VoiceState::SUPPRESS] == true);
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

    QVERIFY(!serializedVoiceState.contains(VoiceState::GUILD_ID));
    QVERIFY(serializedVoiceState[VoiceState::CHANNEL_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[VoiceState::USER_ID] == TEST_STRING1);
    QVERIFY(!serializedVoiceState.contains(VoiceState::MEMBER));
    QVERIFY(serializedVoiceState[VoiceState::SESSION_ID] == TEST_STRING2);
    QVERIFY(serializedVoiceState[VoiceState::DEAF] == true);
    QVERIFY(serializedVoiceState[VoiceState::MUTE] == true);
    QVERIFY(serializedVoiceState[VoiceState::SELF_DEAF] == true);
    QVERIFY(serializedVoiceState[VoiceState::SELF_MUTE] == true);
    QVERIFY(!serializedVoiceState.contains(VoiceState::SELF_STREAM));
    QVERIFY(serializedVoiceState[VoiceState::SUPPRESS] == true);
}

static VoiceStateTest VOICE_STATE_TEST;
