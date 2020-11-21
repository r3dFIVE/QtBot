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

#include "tst_activityassets.h"

#include <payloads/activityassets.h>

void
ActivityAssetsTest::test_serialization_minimal() {
    ActivityAssets assets;

    QJsonObject serializedAssets = assets.toQJsonObject();

    QVERIFY(!serializedAssets.contains(ActivityAssets::LARGE_IMAGE));
    QVERIFY(!serializedAssets.contains(ActivityAssets::LARGE_TEXT));
    QVERIFY(!serializedAssets.contains(ActivityAssets::SMALL_IMAGE));
    QVERIFY(!serializedAssets.contains(ActivityAssets::SMALL_TEXT));
}

void
ActivityAssetsTest::test_serialization_full() {
    ActivityAssets assets;

    assets.setLargeImage(TEST_STRING1);

    assets.setLargeText(TEST_STRING2);

    assets.setSmallImage(TEST_STRING1);

    assets.setSmallText(TEST_STRING2);

    QJsonObject serializedAssets = assets.toQJsonObject();

    QVERIFY(serializedAssets[ActivityAssets::LARGE_IMAGE] == TEST_STRING1);
    QVERIFY(serializedAssets[ActivityAssets::LARGE_IMAGE] != TEST_STRING2);
    QVERIFY(serializedAssets[ActivityAssets::LARGE_TEXT] != TEST_STRING1);
    QVERIFY(serializedAssets[ActivityAssets::LARGE_TEXT] == TEST_STRING2);
    QVERIFY(serializedAssets[ActivityAssets::SMALL_IMAGE] == TEST_STRING1);
    QVERIFY(serializedAssets[ActivityAssets::SMALL_IMAGE] != TEST_STRING2);
    QVERIFY(serializedAssets[ActivityAssets::SMALL_TEXT] != TEST_STRING1);
    QVERIFY(serializedAssets[ActivityAssets::SMALL_TEXT] == TEST_STRING2);
}

void
ActivityAssetsTest::test_deserialization_minimal() {
    ActivityAssets assets(PLD_ACTIVITY_ASSETS_MINIMAL);

    QVERIFY(assets.getLargeImage() == "");
    QVERIFY(assets.getLargeImage() != TEST_STRING1);
    QVERIFY(assets.getLargeText() == "");
    QVERIFY(assets.getLargeText() != TEST_STRING2);
    QVERIFY(assets.getSmallImage() == "");
    QVERIFY(assets.getSmallImage() != TEST_STRING1);
    QVERIFY(assets.getSmallText() == "");
    QVERIFY(assets.getSmallText() != TEST_STRING2);
}

void
ActivityAssetsTest::test_deserialization_full() {
    ActivityAssets assets(PLD_ACTIVITY_ASSETS_FULL);

    QVERIFY(assets.getLargeImage() == TEST_STRING1);
    QVERIFY(assets.getLargeImage() != TEST_STRING2);
    QVERIFY(assets.getLargeText() != TEST_STRING1);
    QVERIFY(assets.getLargeText() == TEST_STRING2);
    QVERIFY(assets.getSmallImage() == TEST_STRING1);
    QVERIFY(assets.getSmallImage() != TEST_STRING2);
    QVERIFY(assets.getSmallText() != TEST_STRING1);
    QVERIFY(assets.getSmallText() == TEST_STRING2);
}

static ActivityAssetsTest ACTIVITY_ASSETS_TEST;
