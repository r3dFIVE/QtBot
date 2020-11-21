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

#include "tst_activity.h"
#include "testpayloads.h"

#include "payloads/activity.h"
#include "payloads/activityassets.h"
#include "payloads/activitysecrets.h"
#include "payloads/activityparty.h"
#include "payloads/activityemoji.h"
#include "payloads/activitytimestamps.h"

class ActivityEmoji;

void
ActivityTest::test_serialization_minimal() {
    Activity activity;

    activity.setName(TEST_STRING1);

    activity.setType(1);

    QJsonObject serializedActivity = activity.toQJsonObject();

    QVERIFY(serializedActivity[Activity::NAME] != "");
    QVERIFY(serializedActivity[Activity::NAME] == TEST_STRING1);

    QVERIFY(serializedActivity[Activity::TYPE] == 1);
    QVERIFY(serializedActivity[Activity::TYPE] != 0);

    QVERIFY(!serializedActivity.contains(Activity::URL));

    /*
     * Note Bot can only send fields "name", "type", and "url"
     */
    QVERIFY(!serializedActivity.contains(Activity::CREATED_AT));
    QVERIFY(!serializedActivity.contains(Activity::TIMESTAMPS));
    QVERIFY(!serializedActivity.contains(Activity::APPLICATION_ID));
    QVERIFY(!serializedActivity.contains(Activity::DETAILS));
    QVERIFY(!serializedActivity.contains(Activity::STATE));
    QVERIFY(!serializedActivity.contains(Activity::EMOJI));
    QVERIFY(!serializedActivity.contains(Activity::PARTY));
    QVERIFY(!serializedActivity.contains(Activity::ASSETS));
    QVERIFY(!serializedActivity.contains(Activity::SECRETS));
    QVERIFY(!serializedActivity.contains(Activity::INSTANCE));
    QVERIFY(!serializedActivity.contains(Activity::FLAGS));
}

void
ActivityTest::test_serialization_full() {
    Activity activity;

    activity.setName(TEST_STRING1);

    activity.setType(1);

    activity.setUrl(TEST_STRING2);

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
    Activity activity(PLD_ACTIVITY_MINIMAL);

    QVERIFY(activity.getName() == TEST_STRING1);
    QVERIFY(activity.getName() != TEST_STRING2);
    QVERIFY(activity.getType() == 1);
    QVERIFY(activity.getType() != 0);
    QVERIFY(activity.getUrl() != TEST_STRING1);
    QVERIFY(activity.getUrl().isUndefined());
    QVERIFY(activity.getCreatedAt() == TEST_INT1);
    QVERIFY(activity.getCreatedAt() != TEST_INT2);
    QVERIFY(activity.getTimestamps().isEmpty());
    QVERIFY(activity.getEmoji().isEmpty());
    QVERIFY(activity.getParty().isEmpty());
    QVERIFY(activity.getAssets().isEmpty());
    QVERIFY(activity.getSecrets().isEmpty());
    QVERIFY(activity.getInstance().isUndefined());
    QVERIFY(activity.getFlags().isUndefined());
}

void
ActivityTest::test_deserialization_full() {
    Activity activity(PLD_ACTIVITY_FULL);

    QVERIFY(activity.getName() == TEST_STRING1);
    QVERIFY(activity.getName() != TEST_STRING2);
    QVERIFY(activity.getType() == 1);
    QVERIFY(activity.getType() != 0);
    QVERIFY(activity.getUrl() != TEST_STRING1);
    QVERIFY(activity.getUrl() == TEST_STRING2);
    QVERIFY(activity.getCreatedAt() == TEST_INT1);
    QVERIFY(activity.getCreatedAt() != TEST_INT2);

    ActivityTimestamps timestamps(activity.getTimestamps());

    QVERIFY(!timestamps.getStart().isNull());
    QVERIFY(timestamps.getStart() == TEST_INT1);
    QVERIFY(timestamps.getStart() != TEST_INT2);
    QVERIFY(!timestamps.getEnd().isNull());
    QVERIFY(timestamps.getEnd() != TEST_INT1);
    QVERIFY(timestamps.getEnd() == TEST_INT2);

    QVERIFY(activity.getApplicationId() == TEST_STRING1);
    QVERIFY(activity.getApplicationId() != TEST_STRING2);
    QVERIFY(activity.getDetails() != TEST_STRING1);
    QVERIFY(activity.getDetails() == TEST_STRING2);
    QVERIFY(activity.getState() == TEST_STRING1);
    QVERIFY(activity.getState() != TEST_STRING2);

    ActivityEmoji emoji(activity.getEmoji());

    QVERIFY(emoji.getName() == TEST_STRING1);
    QVERIFY(emoji.getName() != TEST_STRING2);
    QVERIFY(emoji.getId() != TEST_STRING1);
    QVERIFY(emoji.getId() == TEST_STRING2);
    QVERIFY(!emoji.getAnimated().isNull());
    QVERIFY(emoji.getAnimated() == true);

    ActivityParty party(activity.getParty());

    QVERIFY(party.getId() == TEST_STRING1);
    QVERIFY(party.getId() != TEST_STRING2);
    QVERIFY(party.getSize()[0] == TEST_INT1);
    QVERIFY(party.getSize()[0] != TEST_INT2);
    QVERIFY(party.getSize()[1] != TEST_INT1);
    QVERIFY(party.getSize()[1] == TEST_INT2);

    ActivityAssets assets(activity.getAssets());

    QVERIFY(assets.getLargeImage() == TEST_STRING1);
    QVERIFY(assets.getLargeImage() != TEST_STRING2);
    QVERIFY(assets.getLargeText() != TEST_STRING1);
    QVERIFY(assets.getLargeText() == TEST_STRING2);
    QVERIFY(assets.getSmallImage() == TEST_STRING1);
    QVERIFY(assets.getSmallImage() != TEST_STRING2);
    QVERIFY(assets.getSmallText() != TEST_STRING1);
    QVERIFY(assets.getSmallText() == TEST_STRING2);

    ActivitySecrets secrets(activity.getSecrets());

    QVERIFY(secrets.getJoin() == TEST_STRING1);
    QVERIFY(secrets.getJoin() != TEST_STRING2);
    QVERIFY(secrets.getSpectate() != TEST_STRING1);
    QVERIFY(secrets.getSpectate() == TEST_STRING2);
    QVERIFY(secrets.getMatch() == TEST_STRING1);
    QVERIFY(secrets.getMatch() != TEST_STRING2);

    QVERIFY(!activity.getInstance().isNull());
    QVERIFY(activity.getInstance() == true);
    QVERIFY(activity.getFlags() == 1);
}

static ActivityTest ACTIVITY_TEST;
