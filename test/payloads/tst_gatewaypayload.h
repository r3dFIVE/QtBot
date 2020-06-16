#ifndef TESTGATEWAYPAYLOAD_H
#define TESTGATEWAYPAYLOAD_H

#include <QObject>
#include <testsuite.h>

class GatewayPayloadTest : TestSuite
{
    Q_OBJECT
public:
    GatewayPayloadTest() {}
    ~GatewayPayloadTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // TESTGATEWAYPAYLOAD_H
