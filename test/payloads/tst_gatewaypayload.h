#ifndef TESTGATEWAYPAYLOAD_H
#define TESTGATEWAYPAYLOAD_H

#include <QObject>

#include "testsuite.h"

class GatewayPayloadTest : TestSuite
{
    Q_OBJECT
public:
    GatewayPayloadTest() {}
    ~GatewayPayloadTest() {}

private slots:
    void test_serialization_minimal();
    void test_deserialization_minimal();
    void test_single_value();
};

#endif // TESTGATEWAYPAYLOAD_H
