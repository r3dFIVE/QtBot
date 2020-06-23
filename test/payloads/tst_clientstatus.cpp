#include "tst_clientstatus.h"

#include <payloads/clientstatus.h>

void ClientStatusTest::test_deserialization() {
    ClientStatus clientStatus;
    qDebug() << PLD_CLIENT_STATUS;
    clientStatus.fromQString(PLD_CLIENT_STATUS);

    QVERIFY(clientStatus.getDesktop() == TEST_STRING1);
    QVERIFY(clientStatus.getMobile() == TEST_STRING2);
    QVERIFY(clientStatus.getWeb() == TEST_STRING1);
}

void ClientStatusTest::test_serialization() {
    ClientStatus clientStatus;
    clientStatus.setDesktop(TEST_STRING1);
    clientStatus.setMobile(TEST_STRING2);
    clientStatus.setWeb(TEST_STRING1);

    QJsonObject serializedClientStatus = clientStatus.toQJsonObject();

    QVERIFY(serializedClientStatus[clientStatus.DESKTOP] == TEST_STRING1);
    QVERIFY(serializedClientStatus[clientStatus.MOBILE] == TEST_STRING2);
    QVERIFY(serializedClientStatus[clientStatus.WEB] == TEST_STRING1);
}

static ClientStatusTest CLIENT_STATUS_TEST;
