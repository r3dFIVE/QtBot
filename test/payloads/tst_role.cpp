#include "tst_role.h"

#include "payloads/role.h"

void
RoleTest::test_serialization() {
    Role role;
    role.id = TEST_STRING1;
    role.name = TEST_STRING2;
    role.color = TEST_INT1;
    role.hoist = true;
    role.position = 1;
    role.permissions = TEST_INT2;
    role.managed = true;
    role.mentionable = true;

    QJsonObject serializedRole = role.toQJsonObject();

    QVERIFY(serializedRole[role.ID] == TEST_STRING1);
    QVERIFY(serializedRole[role.NAME] == TEST_STRING2);
    QVERIFY(serializedRole[role.COLOR] == TEST_INT1);
    QVERIFY(serializedRole[role.HOIST] == true);
    QVERIFY(serializedRole[role.POSITION] == 1);
    QVERIFY(serializedRole[role.PERMISSIONS] == TEST_INT2);
    QVERIFY(serializedRole[role.MANAGED] == true);
    QVERIFY(serializedRole[role.MENTIONABLE] == true);
}

void
RoleTest::test_deserialization() {
    Role role;
    role.fromQString(PLD_ROLE);

    QVERIFY(role.id == TEST_STRING1);
    QVERIFY(role.name == TEST_STRING2);
    QVERIFY(role.color == TEST_INT1);
    QVERIFY(role.hoist == true);
    QVERIFY(role.position == 1);
    QVERIFY(role.permissions == TEST_INT2);
    QVERIFY(role.managed == true);
    QVERIFY(role.mentionable == true);
}

static RoleTest ROLE_TEST;
