#ifndef ASSETSTEST_H
#define ASSETSTEST_H

#include "testsuite.h"

class AssetsTest : public TestSuite
{
    Q_OBJECT

public:
    AssetsTest() {}
    ~AssetsTest() {};

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // ASSETSTEST_H
