#include "tst_assets.h"
#include "testpayloads.h"

#include <payloads/assets.h>

void
AssetsTest::test_serialization_minimal() {
    Assets assets;

    QJsonObject serializedAssets = assets.toQJsonObject();

    QVERIFY(!serializedAssets.contains(assets.LARGE_IMAGE));
    QVERIFY(!serializedAssets.contains(assets.LARGE_TEXT));
    QVERIFY(!serializedAssets.contains(assets.SMALL_IMAGE));
    QVERIFY(!serializedAssets.contains(assets.SMALL_TEXT));
}

void
AssetsTest::test_serialization_full() {
    Assets assets;
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
AssetsTest::test_deserialization_minimal() {
    Assets assets;
    assets.fromQString(PLD_ASSETS_MINIMAL);

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
AssetsTest::test_deserialization_full() {
    Assets assets;
    QString s = PLD_ASSETS_FULL;
    assets.fromQString(PLD_ASSETS_FULL);

    QVERIFY(assets.large_image == TEST_STRING1);
    QVERIFY(assets.large_image != TEST_STRING2);

    QVERIFY(assets.large_text != TEST_STRING1);
    QVERIFY(assets.large_text == TEST_STRING2);

    QVERIFY(assets.small_image == TEST_STRING1);
    QVERIFY(assets.small_image != TEST_STRING2);

    QVERIFY(assets.small_text != TEST_STRING1);
    QVERIFY(assets.small_text == TEST_STRING2);
}

static AssetsTest ASSETS_TEST;
