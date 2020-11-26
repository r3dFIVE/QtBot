/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "tst_role.h"

#include "payloads/role.h"

void
RoleTest::test_serialization() {
    Role role;

    role.setId(TEST_STRING1);

    role.setName(TEST_STRING2);

    role.setColor(TEST_INT1);

    role.setHoist(true);

    role.setPosition(1);

    role.setPermissions(TEST_INT2);

    role.setManaged(true);

    role.setMentionable(true);

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
    Role role(PLD_ROLE);

    QVERIFY(role.getId() == TEST_STRING1);
    QVERIFY(role.getName() == TEST_STRING2);
    QVERIFY(role.getColor() == TEST_INT1);
    QVERIFY(role.getHoist() == true);
    QVERIFY(role.getPosition() == 1);
    QVERIFY(role.getPermissions() == TEST_INT2);
    QVERIFY(role.getManaged() == true);
    QVERIFY(role.getMentionable() == true);
}

static RoleTest ROLE_TEST;
