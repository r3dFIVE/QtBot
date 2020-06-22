#include "tst_user.h"
#include "testpayloads.h"

#include <payloads/user.h>

void
UserTest::test_serialization_minimal() {
    User user;
    user.id = TEST_STRING1;
    user.username = TEST_STRING2;
    user.discriminator = TEST_STRING1;

    QJsonObject serializedUser = user.toQJsonObject();

    QVERIFY(serializedUser[user.ID] == TEST_STRING1);
    QVERIFY(serializedUser[user.ID] != TEST_STRING2);

    QVERIFY(serializedUser[user.USERNAME] != TEST_STRING1);
    QVERIFY(serializedUser[user.USERNAME] == TEST_STRING2);

    QVERIFY(serializedUser[user.DISCRIMINATOR] == TEST_STRING1);
    QVERIFY(serializedUser[user.DISCRIMINATOR] != TEST_STRING2);
}

void
UserTest::test_serialization_full() {
    User user;
    user.id = TEST_STRING1;
    user.username = TEST_STRING2;
    user.discriminator = TEST_STRING1;
    user.avatar = TEST_STRING2;
    user.bot = QSharedPointer<bool>(new bool(true));
    user.system = QSharedPointer<bool>(new bool(true));
    user.mfa_enabled = QSharedPointer<bool>(new bool(true));
    user.locale = TEST_STRING1;
    user.verified = QSharedPointer<bool>(new bool(true));
    user.email = TEST_STRING2;
    user.flags = QSharedPointer<int>(new int(1));
    user.premium_type = QSharedPointer<int>(new int(1));
    user.public_flags = QSharedPointer<int>(new int(1));

    QJsonObject serializedUser = user.toQJsonObject();

    QVERIFY(serializedUser[user.ID] == TEST_STRING1);
    QVERIFY(serializedUser[user.ID] != TEST_STRING2);

    QVERIFY(serializedUser[user.USERNAME] != TEST_STRING1);
    QVERIFY(serializedUser[user.USERNAME] == TEST_STRING2);

    QVERIFY(serializedUser[user.DISCRIMINATOR] == TEST_STRING1);
    QVERIFY(serializedUser[user.DISCRIMINATOR] != TEST_STRING2);

    QVERIFY(serializedUser[user.AVATAR] != TEST_STRING1);
    QVERIFY(serializedUser[user.AVATAR] == TEST_STRING2);

    QVERIFY(serializedUser.contains(user.BOT));
    QVERIFY(serializedUser[user.BOT] == true);

    QVERIFY(serializedUser.contains(user.SYSTEM));
    QVERIFY(serializedUser[user.SYSTEM] == true);

    QVERIFY(serializedUser.contains(user.MFA_ENABLED));
    QVERIFY(serializedUser[user.MFA_ENABLED] == true);

    QVERIFY(serializedUser[user.LOCALE] == TEST_STRING1);
    QVERIFY(serializedUser[user.LOCALE] != TEST_STRING2);

    QVERIFY(serializedUser.contains(user.VERIFIED));
    QVERIFY(serializedUser[user.VERIFIED] == true);

    QVERIFY(serializedUser[user.EMAIL] != TEST_STRING1);
    QVERIFY(serializedUser[user.EMAIL] == TEST_STRING2);

    QVERIFY(serializedUser.contains(user.FLAGS));
    QVERIFY(serializedUser[user.FLAGS] == 1);

    QVERIFY(serializedUser.contains(user.PREMIUM_TYPE));
    QVERIFY(serializedUser[user.PUBLIC_FLAGS] == 1);

    QVERIFY(serializedUser.contains(user.PUBLIC_FLAGS));
    QVERIFY(serializedUser[user.PUBLIC_FLAGS] == 1);
}

void
UserTest::test_deserialization_minimal() {
    User user;
    user.fromQString(PLD_USER_MINIMAL);

    QVERIFY(user.id == TEST_STRING1);
    QVERIFY(user.id != TEST_STRING2);

    QVERIFY(user.username != TEST_STRING1);
    QVERIFY(user.username == TEST_STRING2);

    QVERIFY(user.discriminator == TEST_STRING1);
    QVERIFY(user.discriminator != TEST_STRING2);
}

void
UserTest::test_deserialization_full() {
    User user;
    user.fromQString(PLD_USER_FULL);

    QVERIFY(user.id == TEST_STRING1);
    QVERIFY(user.id != TEST_STRING2);

    QVERIFY(user.username != TEST_STRING1);
    QVERIFY(user.username == TEST_STRING2);

    QVERIFY(user.discriminator == TEST_STRING1);
    QVERIFY(user.discriminator != TEST_STRING2);

    QVERIFY(user.avatar != TEST_STRING1);
    QVERIFY(user.avatar == TEST_STRING2);

    QVERIFY(user.bot != nullptr);
    QVERIFY(*user.bot == true);

    QVERIFY(user.system != nullptr);
    QVERIFY(*user.system == true);

    QVERIFY(user.mfa_enabled != nullptr);
    QVERIFY(*user.mfa_enabled == true);

    QVERIFY(user.locale == TEST_STRING1);
    QVERIFY(user.locale != TEST_STRING2);

    QVERIFY(user.verified != nullptr);
    QVERIFY(*user.verified == true);

    QVERIFY(user.locale == TEST_STRING1);
    QVERIFY(user.locale != TEST_STRING2);

    QVERIFY(user.flags != nullptr);
    QVERIFY(*user.flags == 1);

    QVERIFY(user.premium_type != nullptr);
    QVERIFY(*user.premium_type == 1);

    QVERIFY(user.public_flags != nullptr);
    QVERIFY(*user.public_flags == 1);
}

static UserTest USER_TEST;
