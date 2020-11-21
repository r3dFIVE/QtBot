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
