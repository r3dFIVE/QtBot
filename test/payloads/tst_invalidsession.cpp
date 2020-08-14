#include "tst_invalidsession.h"

#include <payloads/invalidsession.h>

void
InvalidSessionTest::test_deserialization() {
    InvalidSession invalidSession(PLD_INVALID_SESSION);

    QVERIFY(invalidSession.getD() == true);
    QVERIFY(invalidSession.getOP() == GatewayEvent::INVALID_SESSION);
}

static InvalidSessionTest INVALID_SESSION_TEST;
