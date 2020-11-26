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

#include "tst_user.h"

#include "payloads/user.h"

void
UserTest::test_serialization_minimal() {
    User user;

    user.setId(TEST_STRING1);

    user.setUsername(TEST_STRING2);

    user.setDiscriminator(TEST_STRING1);

    QJsonObject serializedUser = user.toQJsonObject();

    QVERIFY(serializedUser[User::ID] == TEST_STRING1);
    QVERIFY(serializedUser[User::ID] != TEST_STRING2);
    QVERIFY(serializedUser[User::USERNAME] != TEST_STRING1);
    QVERIFY(serializedUser[User::USERNAME] == TEST_STRING2);
    QVERIFY(serializedUser[User::DISCRIMINATOR] == TEST_STRING1);
    QVERIFY(serializedUser[User::DISCRIMINATOR] != TEST_STRING2);
}

void
UserTest::test_serialization_full() {
    User user;

    user.setId(TEST_STRING1);

    user.setUsername(TEST_STRING2);

    user.setDiscriminator(TEST_STRING1);

    user.setAvatar(TEST_STRING2);

    user.setBot(true);

    user.setSystem(true);

    user.setMfaEnabled(true);

    user.setLocale(TEST_STRING1);

    user.setVerified(true);

    user.setEmail(TEST_STRING2);

    user.setFlags(1);

    user.setPremiumType(1);

    user.setPublicFlags(1);

    QJsonObject serializedUser = user.toQJsonObject();

    QVERIFY(serializedUser[User::ID] == TEST_STRING1);
    QVERIFY(serializedUser[User::ID] != TEST_STRING2);
    QVERIFY(serializedUser[User::USERNAME] != TEST_STRING1);
    QVERIFY(serializedUser[User::USERNAME] == TEST_STRING2);
    QVERIFY(serializedUser[User::DISCRIMINATOR] == TEST_STRING1);
    QVERIFY(serializedUser[User::DISCRIMINATOR] != TEST_STRING2);
    QVERIFY(serializedUser[User::AVATAR] != TEST_STRING1);
    QVERIFY(serializedUser[User::AVATAR] == TEST_STRING2);
    QVERIFY(serializedUser.contains(User::BOT));
    QVERIFY(serializedUser[User::BOT] == true);
    QVERIFY(serializedUser.contains(User::SYSTEM));
    QVERIFY(serializedUser[User::SYSTEM] == true);
    QVERIFY(serializedUser.contains(User::MFA_ENABLED));
    QVERIFY(serializedUser[User::MFA_ENABLED] == true);
    QVERIFY(serializedUser[User::LOCALE] == TEST_STRING1);
    QVERIFY(serializedUser[User::LOCALE] != TEST_STRING2);
    QVERIFY(serializedUser.contains(User::VERIFIED));
    QVERIFY(serializedUser[User::VERIFIED] == true);
    QVERIFY(serializedUser[User::EMAIL] != TEST_STRING1);
    QVERIFY(serializedUser[User::EMAIL] == TEST_STRING2);
    QVERIFY(serializedUser.contains(User::FLAGS));
    QVERIFY(serializedUser[User::FLAGS] == 1);
    QVERIFY(serializedUser.contains(User::PREMIUM_TYPE));
    QVERIFY(serializedUser[User::PUBLIC_FLAGS] == 1);
    QVERIFY(serializedUser.contains(User::PUBLIC_FLAGS));
    QVERIFY(serializedUser[User::PUBLIC_FLAGS] == 1);
}

void
UserTest::test_deserialization_minimal() {
    User user(PLD_USER_MINIMAL);

    QVERIFY(user.getId() == TEST_STRING1);
    QVERIFY(user.getId() != TEST_STRING2);
    QVERIFY(user.getUsername() != TEST_STRING1);
    QVERIFY(user.getUsername() == TEST_STRING2);
    QVERIFY(user.getDiscriminator() == TEST_STRING1);
    QVERIFY(user.getDiscriminator() != TEST_STRING2);
}

void
UserTest::test_deserialization_full() {
    User user(PLD_USER_FULL);

    QVERIFY(user.getId() == TEST_STRING1);
    QVERIFY(user.getId() != TEST_STRING2);
    QVERIFY(user.getUsername() != TEST_STRING1);
    QVERIFY(user.getUsername() == TEST_STRING2);
    QVERIFY(user.getDiscriminator() == TEST_STRING1);
    QVERIFY(user.getDiscriminator() != TEST_STRING2);
    QVERIFY(user.getAvatar() != TEST_STRING1);
    QVERIFY(user.getAvatar() == TEST_STRING2);
    QVERIFY(user.getBot() == true);
    QVERIFY(user.getSystem() == true);
    QVERIFY(user.getMfaEnabled() == true);
    QVERIFY(user.getLocale() == TEST_STRING1);
    QVERIFY(user.getLocale() != TEST_STRING2);
    QVERIFY(user.getVerified() == true);
    QVERIFY(user.getFlags() == 1);
    QVERIFY(user.getPremiumType() == 1);
    QVERIFY(user.getPublicFlags() == 1);
}

static UserTest USER_TEST;
