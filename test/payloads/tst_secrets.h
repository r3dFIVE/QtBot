#ifndef SECRETSTEST_H
#define SECRETSTEST_H

#include "testsuite.h"

#include <QObject>

class SecretsTest : public TestSuite
{
    Q_OBJECT
public:
    SecretsTest() {}
    ~SecretsTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // SECRETSTEST_H
