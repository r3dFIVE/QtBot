#include "tst_updatestatus.h"

#include <payloads/updatestatus.h>


void
UpdateStatusTest::test_deserialization() {
    UpdateStatus updateStatus;
    updateStatus.fromQString(PLD_UPDATE_STATUS);

    QVERIFY(updateStatus.since);
    QVERIFY(updateStatus.getSince() == TEST_INT1);
    QVERIFY(updateStatus.game);
    Activity game;
    game.fromQJsonObject(updateStatus.game->toQJsonObject());
    QVERIFY(game.getName() == TEST_STRING1);
    QVERIFY(updateStatus.getStatus() == TEST_STRING1);
    QVERIFY(updateStatus.getAfk() == true);
}


void
UpdateStatusTest::test_serialization() {
    UpdateStatus updateStatus;
    updateStatus.setSince(TEST_INT1);
    Activity game;
    game.fromQString(PLD_ACTIVITY_MINIMAL);
    updateStatus.setGame(game.toQJsonObject());
    updateStatus.setStatus(TEST_STRING1);
    updateStatus.setAfk(true);

    QJsonObject serializedUpdateStatus = updateStatus.toQJsonObject();
    QVERIFY(serializedUpdateStatus[updateStatus.SINCE] == TEST_INT1);
    Activity serializedGame;
    serializedGame.fromQJsonObject(serializedUpdateStatus[updateStatus.GAME].toObject());
    QVERIFY(serializedGame.getName() == TEST_STRING1);
    QVERIFY(serializedUpdateStatus[updateStatus.STATUS] == TEST_STRING1);
    QVERIFY(serializedUpdateStatus[updateStatus.AFK] == true);
}

static UpdateStatusTest UPDATE_STATUS_TEST;
