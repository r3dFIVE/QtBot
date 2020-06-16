#include "testsuite.h"

TestSuite::TestSuite()
{
    suite().push_back(this);
}

QList<TestSuite*> & TestSuite::suite() {
    static QList<TestSuite*> tests;
    return tests;
}
