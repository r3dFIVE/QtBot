#include "tst_permissionoverwrite.h"

#include <payloads/permissionoverwrite.h>


void PermissionOverwriteTest::test_serialization() {
    PermissionOverwrite permissionOverwrite;
    permissionOverwrite.setId(TEST_STRING1);
    permissionOverwrite.setType(TEST_STRING2);
    permissionOverwrite.setAllow(TEST_INT1);
    permissionOverwrite.setDeny(TEST_INT2);

    QJsonObject serializedPermissionOverwrite = permissionOverwrite.toQJsonObject();

    QVERIFY(serializedPermissionOverwrite[permissionOverwrite.ID] == TEST_STRING1);
    QVERIFY(serializedPermissionOverwrite[permissionOverwrite.TYPE] == TEST_STRING2);
    QVERIFY(serializedPermissionOverwrite[permissionOverwrite.ALLOW] == TEST_INT1);
    QVERIFY(serializedPermissionOverwrite[permissionOverwrite.DENY] == TEST_INT2);
}

void PermissionOverwriteTest::test_deserialization() {
    PermissionOverwrite permissionOverwrite;
    qDebug() << PLD_PERMISSION_OVERWRITE;
    permissionOverwrite.fromQString(PLD_PERMISSION_OVERWRITE);

    QVERIFY(permissionOverwrite.getId() == TEST_STRING1);
    QVERIFY(permissionOverwrite.getType() == TEST_STRING2);
    QVERIFY(permissionOverwrite.getAllow() == TEST_INT1);
    QVERIFY(permissionOverwrite.getDeny() == TEST_INT2);
}

static PermissionOverwriteTest PERMISSION_OVERWRITE_TEST;
