#include "tst_invalidsession.h"

#include <payloads/invalidsession.h>

void
InvalidSessionTest::test_deserialization() {
    InvalidSession invalidSession;
    invalidSession.fromQString(PLD_INVALID_SESSION);

    QVERIFY(invalidSession.d == true);
    QVERIFY(invalidSession.op == GatewayEvents::INVALID_SESSION);
}

static InvalidSessionTest INVALID_SESSION_TEST;
