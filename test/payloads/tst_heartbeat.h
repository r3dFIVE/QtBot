#include "payloads/heartbeat.h"
#include "testpayloads.h"
#include "testsuite.h"

class HeartbeatTest : public TestSuite
{
    Q_OBJECT

public:
    HeartbeatTest() {};
    ~HeartbeatTest() {};

private slots:
    void test_serialization();
    void test_deserialization();
};

