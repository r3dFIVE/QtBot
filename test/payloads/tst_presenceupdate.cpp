#include "tst_presenceupdate.h"

#include "payloads/presenceupdate.h"
#include "payloads/user.h"
#include "payloads/activity.h"
#include "payloads/clientstatus.h"


void
PresenceUpdateTest::test_serialization_minimal() {
    PresenceUpdate presenceUpdate;

    User user(PLD_USER_MINIMAL);

    presenceUpdate.setUser(user.toQJsonObject());

    QJsonArray roles = { TEST_STRING1, TEST_STRING2 };

    presenceUpdate.setRoles(roles);

    presenceUpdate.setGuildId(TEST_STRING1);

    presenceUpdate.setStatus(TEST_STRING2);

    Activity activity(PLD_ACTIVITY_MINIMAL);

    QJsonArray activities = { activity.toQJsonObject() };

    presenceUpdate.setActivities(activities);

    ClientStatus clientStatus(PLD_CLIENT_STATUS);

    presenceUpdate.setClientStatus(clientStatus.toQJsonObject());

    QJsonObject serializedPresenceUpdate = presenceUpdate.toQJsonObject();

    QVERIFY(serializedPresenceUpdate[presenceUpdate.USER].toObject()[user.ID] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.ROLES].toArray()[0] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.ROLES].toArray()[1] == TEST_STRING2);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.GAME].isNull());
    QVERIFY(serializedPresenceUpdate[presenceUpdate.GUILD_ID] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.STATUS] == TEST_STRING2);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.ACTIVITIES].toArray()[0].toObject()[activity.NAME] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.CLIENT_STATUS].toObject()[clientStatus.DESKTOP] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.PREMIUM_SINCE].isNull());
    QVERIFY(serializedPresenceUpdate[presenceUpdate.NICK].isNull());
}

void
PresenceUpdateTest::test_serialization_full() {
    PresenceUpdate presenceUpdate;

    User user(PLD_USER_MINIMAL);

    presenceUpdate.setUser(user.toQJsonObject());

    QJsonArray roles = { TEST_STRING1, TEST_STRING2 };

    presenceUpdate.setRoles(roles);

    Activity activity(PLD_ACTIVITY_MINIMAL);

    presenceUpdate.setGame(activity.toQJsonObject());

    presenceUpdate.setGuildId(TEST_STRING1);

    presenceUpdate.setStatus(TEST_STRING2);

    QJsonArray activities = { activity.toQJsonObject() };

    presenceUpdate.setActivities(activities);

    ClientStatus clientStatus(PLD_CLIENT_STATUS);

    presenceUpdate.setClientStatus(clientStatus.toQJsonObject());

    presenceUpdate.setPremiumSince(TEST_STRING1);

    presenceUpdate.setNick(TEST_STRING2);

    QJsonObject serializedPresenceUpdate = presenceUpdate.toQJsonObject();

    QVERIFY(serializedPresenceUpdate[presenceUpdate.USER].toObject()[user.ID] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.ROLES].toArray()[0] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.ROLES].toArray()[1] == TEST_STRING2);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.GAME].toObject()[activity.NAME] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.GUILD_ID] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.STATUS] == TEST_STRING2);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.ACTIVITIES].toArray()[0].toObject()[activity.NAME] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.CLIENT_STATUS].toObject()[clientStatus.DESKTOP] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.PREMIUM_SINCE] == TEST_STRING1);
    QVERIFY(serializedPresenceUpdate[presenceUpdate.NICK] == TEST_STRING2);
}

void
PresenceUpdateTest::test_deserialization_minimal() {
    PresenceUpdate presenceUpdate(PLD_PRESENCE_UPDATE_MINIMAL);

    User user(presenceUpdate.getUser());

    QVERIFY(user.getId() == TEST_STRING1);
    QVERIFY(presenceUpdate.getRoles()[0].toString() == TEST_STRING1);
    QVERIFY(presenceUpdate.getRoles()[1].toString() == TEST_STRING2);
    QVERIFY(presenceUpdate.getGame().isEmpty());
    QVERIFY(presenceUpdate.getGuildId() == TEST_STRING1);

    ClientStatus clientStatus(presenceUpdate.getClientStatus());

    QVERIFY(clientStatus.getDesktop() == TEST_STRING1);
    QVERIFY(presenceUpdate.getPremiumSince().isUndefined());
    QVERIFY(presenceUpdate.getNick().isUndefined());
}

void
PresenceUpdateTest::test_deserialization_full() {
    PresenceUpdate presenceUpdate(PLD_PRESENCE_UPDATE_FULL);

    User user(presenceUpdate.getUser());

    QVERIFY(user.getId() == TEST_STRING1);
    QVERIFY(presenceUpdate.getRoles()[0].toString() == TEST_STRING1);
    QVERIFY(presenceUpdate.getRoles()[1].toString() == TEST_STRING2);

    Activity game(presenceUpdate.getGame());

    QVERIFY(game.getName() == TEST_STRING1);
    QVERIFY(presenceUpdate.getGuildId() == TEST_STRING1);

    ClientStatus clientStatus(presenceUpdate.getClientStatus());

    QVERIFY(clientStatus.getDesktop() == TEST_STRING1);
    QVERIFY(presenceUpdate.getPremiumSince() == TEST_STRING1);
    QVERIFY(presenceUpdate.getNick() == TEST_STRING2);
}

static PresenceUpdateTest PRESENCE_UPDATE_TEST;
