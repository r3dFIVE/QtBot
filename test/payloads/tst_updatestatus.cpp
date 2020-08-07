#include "tst_updatestatus.h"

#include "payloads/activity.h"
#include "payloads/updatestatus.h"


void
UpdateStatusTest::test_deserialization() {
    UpdateStatus updateStatus(PLD_UPDATE_STATUS);

    QVERIFY(updateStatus.getSince() == TEST_INT1);

    Activity game(updateStatus.getGame());

    QVERIFY(game.getName() == TEST_STRING1);
    QVERIFY(updateStatus.getStatus() == TEST_STRING1);
    QVERIFY(updateStatus.getAfk() == true);
}


void
UpdateStatusTest::test_serialization() {
    UpdateStatus updateStatus;

    updateStatus.setSince(TEST_INT1);

    Activity game(PLD_ACTIVITY_MINIMAL);

    updateStatus.setGame(game.toQJsonObject());

    updateStatus.setStatus(TEST_STRING1);

    updateStatus.setAfk(true);

    QJsonObject serializedUpdateStatus = updateStatus.toQJsonObject();

    QVERIFY(serializedUpdateStatus[UpdateStatus::SINCE] == TEST_INT1);

    Activity serializedGame(serializedUpdateStatus[updateStatus.GAME].toObject());

    QVERIFY(serializedGame.getName() == TEST_STRING1);
    QVERIFY(serializedUpdateStatus[UpdateStatus::STATUS] == TEST_STRING1);
    QVERIFY(serializedUpdateStatus[UpdateStatus::AFK] == true);
}

static UpdateStatusTest UPDATE_STATUS_TEST;
