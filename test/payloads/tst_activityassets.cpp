#include "tst_activityassets.h"

#include <payloads/activityassets.h>

void
ActivityAssetsTest::test_serialization_minimal() {
    ActivityAssets assets;

    QJsonObject serializedAssets = assets.toQJsonObject();

    QVERIFY(!serializedAssets.contains(assets.LARGE_IMAGE));
    QVERIFY(!serializedAssets.contains(assets.LARGE_TEXT));
    QVERIFY(!serializedAssets.contains(assets.SMALL_IMAGE));
    QVERIFY(!serializedAssets.contains(assets.SMALL_TEXT));
}

void
ActivityAssetsTest::test_serialization_full() {
    ActivityAssets assets;
    assets.large_image = TEST_STRING1;
    assets.large_text = TEST_STRING2;
    assets.small_image = TEST_STRING1;
    assets.small_text = TEST_STRING2;

    QJsonObject serializedAssets = assets.toQJsonObject();

    QVERIFY(serializedAssets[assets.LARGE_IMAGE] == TEST_STRING1);
    QVERIFY(serializedAssets[assets.LARGE_IMAGE] != TEST_STRING2);

    QVERIFY(serializedAssets[assets.LARGE_TEXT] != TEST_STRING1);
    QVERIFY(serializedAssets[assets.LARGE_TEXT] == TEST_STRING2);

    QVERIFY(serializedAssets[assets.SMALL_IMAGE] == TEST_STRING1);
    QVERIFY(serializedAssets[assets.SMALL_IMAGE] != TEST_STRING2);

    QVERIFY(serializedAssets[assets.SMALL_TEXT] != TEST_STRING1);
    QVERIFY(serializedAssets[assets.SMALL_TEXT] == TEST_STRING2);
}

void
ActivityAssetsTest::test_deserialization_minimal() {
    ActivityAssets assets;
    assets.fromQString(PLD_ACTIVITY_ASSETS_MINIMAL);

    QVERIFY(assets.large_image == "");
    QVERIFY(assets.large_image != TEST_STRING1);

    QVERIFY(assets.large_text == "");
    QVERIFY(assets.large_text != TEST_STRING2);

    QVERIFY(assets.small_image == "");
    QVERIFY(assets.small_image != TEST_STRING1);

    QVERIFY(assets.small_text == "");
    QVERIFY(assets.small_text != TEST_STRING2);
}

void
ActivityAssetsTest::test_deserialization_full() {
    ActivityAssets assets;
    assets.fromQString(PLD_ACTIVITY_ASSETS_FULL);

    QVERIFY(assets.large_image == TEST_STRING1);
    QVERIFY(assets.large_image != TEST_STRING2);

    QVERIFY(assets.large_text != TEST_STRING1);
    QVERIFY(assets.large_text == TEST_STRING2);

    QVERIFY(assets.small_image == TEST_STRING1);
    QVERIFY(assets.small_image != TEST_STRING2);

    QVERIFY(assets.small_text != TEST_STRING1);
    QVERIFY(assets.small_text == TEST_STRING2);
}

static ActivityAssetsTest ACTIVITY_ASSETS_TEST;
