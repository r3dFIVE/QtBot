#include "tst_activity.h"
#include "testpayloads.h"

#include <payloads/activity.h>

void
ActivityTest::test_serialization_minimal() {
    Activity activity;
    activity.name = TEST_STRING1;
    activity.type = 1;

    QJsonObject serializedActivity = activity.toQJsonObject();

    QVERIFY(serializedActivity[activity.NAME] != "");
    QVERIFY(serializedActivity[activity.NAME] == TEST_STRING1);

    QVERIFY(serializedActivity[activity.TYPE] == 1);
    QVERIFY(serializedActivity[activity.TYPE] != 0);

    QVERIFY(!serializedActivity.contains(activity.URL));

    /*
     * Note Bot can only send fields "name", "type", and "url"
     */
    QVERIFY(!serializedActivity.contains(activity.CREATED_AT));
    QVERIFY(!serializedActivity.contains(activity.TIMESTAMPS));
    QVERIFY(!serializedActivity.contains(activity.APPLICATION_ID));
    QVERIFY(!serializedActivity.contains(activity.DETAILS));
    QVERIFY(!serializedActivity.contains(activity.STATE));
    QVERIFY(!serializedActivity.contains(activity.EMOJI));
    QVERIFY(!serializedActivity.contains(activity.PARTY));
    QVERIFY(!serializedActivity.contains(activity.ASSETS));
    QVERIFY(!serializedActivity.contains(activity.SECRETS));
    QVERIFY(!serializedActivity.contains(activity.INSTANCE));
    QVERIFY(!serializedActivity.contains(activity.FLAGS));
}

void
ActivityTest::test_serialization_full() {
    Activity activity;
    activity.name = TEST_STRING1;
    activity.type = 1;
    activity.url = TEST_STRING2;

    QJsonObject serializedActivity = activity.toQJsonObject();

    QVERIFY(serializedActivity[activity.NAME] != "");
    QVERIFY(serializedActivity[activity.NAME] == TEST_STRING1);

    QVERIFY(serializedActivity[activity.TYPE] == 1);
    QVERIFY(serializedActivity[activity.TYPE] != 0);

    QVERIFY(serializedActivity[activity.URL] != "");
    QVERIFY(serializedActivity[activity.URL] == TEST_STRING2);

    /*
     * Note Bot can only send fields "name", "type", and "url"
     */
    QVERIFY(!serializedActivity.contains(activity.CREATED_AT));
    QVERIFY(!serializedActivity.contains(activity.TIMESTAMPS));
    QVERIFY(!serializedActivity.contains(activity.APPLICATION_ID));
    QVERIFY(!serializedActivity.contains(activity.DETAILS));
    QVERIFY(!serializedActivity.contains(activity.STATE));
    QVERIFY(!serializedActivity.contains(activity.EMOJI));
    QVERIFY(!serializedActivity.contains(activity.PARTY));
    QVERIFY(!serializedActivity.contains(activity.ASSETS));
    QVERIFY(!serializedActivity.contains(activity.SECRETS));
    QVERIFY(!serializedActivity.contains(activity.INSTANCE));
    QVERIFY(!serializedActivity.contains(activity.FLAGS));
}

void
ActivityTest::test_deserialization_minimal() {
    Activity activity;
    activity.fromQString(PLD_ACTIVITY_MINIMAL);

    QVERIFY(activity.name == TEST_STRING1);
    QVERIFY(activity.name != TEST_STRING2);

    QVERIFY(activity.type == 1);
    QVERIFY(activity.type != 0);

    QVERIFY(activity.url != TEST_STRING1);
    QVERIFY(activity.url == "");

    QVERIFY(activity.created_at == TEST_INT1);
    QVERIFY(activity.created_at != TEST_INT2);

    QVERIFY(activity.timestamps == nullptr);
    QVERIFY(activity.emoji == nullptr);
    QVERIFY(activity.party == nullptr);
    QVERIFY(activity.assets == nullptr);
    QVERIFY(activity.secrets == nullptr);
    QVERIFY(activity.instance == nullptr);
    QVERIFY(activity.flags == nullptr);
}

void
ActivityTest::test_deserialization_full() {
    Activity activity;
    activity.fromQString(PLD_ACTIVITY_FULL);

    QVERIFY(activity.name == TEST_STRING1);
    QVERIFY(activity.name != TEST_STRING2);

    QVERIFY(activity.type == 1);
    QVERIFY(activity.type != 0);

    QVERIFY(activity.url != TEST_STRING1);
    QVERIFY(activity.url == TEST_STRING2);

    QVERIFY(activity.created_at == TEST_INT1);
    QVERIFY(activity.created_at != TEST_INT2);

    ActivityTimestamps timestamps;
    timestamps.fromQJsonObject(activity.timestamps->toQJsonObject());

    QVERIFY(timestamps.start != nullptr);
    QVERIFY(*timestamps.start == TEST_INT1);
    QVERIFY(*timestamps.start != TEST_INT2);

    QVERIFY(timestamps.end != nullptr);
    QVERIFY(*timestamps.end != TEST_INT1);
    QVERIFY(*timestamps.end == TEST_INT2);

    QVERIFY(activity.application_id == TEST_STRING1);
    QVERIFY(activity.application_id != TEST_STRING2);

    QVERIFY(activity.details != TEST_STRING1);
    QVERIFY(activity.details == TEST_STRING2);

    QVERIFY(activity.state == TEST_STRING1);
    QVERIFY(activity.state != TEST_STRING2);

    ActivityEmoji emoji;
    emoji.fromQJsonObject(activity.emoji->toQJsonObject());

    QVERIFY(emoji.name == TEST_STRING1);
    QVERIFY(emoji.name != TEST_STRING2);

    QVERIFY(emoji.id != TEST_STRING1);
    QVERIFY(emoji.id == TEST_STRING2);

    QVERIFY(emoji.animated != nullptr);
    QVERIFY(*emoji.animated ==  true);
    QVERIFY(*emoji.animated != false);

    ActivityParty party;
    party.fromQJsonObject(activity.party->toQJsonObject());

    QVERIFY(party.id == TEST_STRING1);
    QVERIFY(party.id != TEST_STRING2);

    QVERIFY(party.size[0] != nullptr);
    QVERIFY(*party.size[0] == TEST_INT1);
    QVERIFY(*party.size[0] != TEST_INT2);

    QVERIFY(party.size[1] != nullptr);
    QVERIFY(*party.size[1] != TEST_INT1);
    QVERIFY(*party.size[1] == TEST_INT2);

    ActivityAssets assets;
    assets.fromQJsonObject(activity.assets->toQJsonObject());

    QVERIFY(assets.large_image == TEST_STRING1);
    QVERIFY(assets.large_image != TEST_STRING2);

    QVERIFY(assets.large_text != TEST_STRING1);
    QVERIFY(assets.large_text == TEST_STRING2);

    QVERIFY(assets.small_image == TEST_STRING1);
    QVERIFY(assets.small_image != TEST_STRING2);

    QVERIFY(assets.small_text != TEST_STRING1);
    QVERIFY(assets.small_text == TEST_STRING2);

    ActivitySecrets secrets;
    secrets.fromQJsonObject(activity.secrets->toQJsonObject());

    QVERIFY(secrets.join == TEST_STRING1);
    QVERIFY(secrets.join != TEST_STRING2);

    QVERIFY(secrets.spectate != TEST_STRING1);
    QVERIFY(secrets.spectate == TEST_STRING2);

    QVERIFY(secrets.match == TEST_STRING1);
    QVERIFY(secrets.match != TEST_STRING2);

    QVERIFY(activity.instance != nullptr);
    QVERIFY(*activity.instance == true);

    QVERIFY(activity.flags != nullptr);
    QVERIFY(*activity.flags == 1);
}

static ActivityTest ACTIVITY_TEST;
