#ifndef ASSETSTEST_H
#define ASSETSTEST_H

#include "testsuite.h"

class ActivityAssetsTest : public TestSuite
{
    Q_OBJECT

public:
    ActivityAssetsTest() {}
    ~ActivityAssetsTest() {};

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // ASSETSTEST_H
