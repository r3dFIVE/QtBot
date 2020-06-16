#include <QList>

#include "tests.h"
#include "testsuite.h"

int main(int argc, char** argv) {
    int status = 0;

    QListIterator<TestSuite*> it(TestSuite::suite());
    while(it.hasNext()) {
        {
            TestSuite *test = it.next();
            status |= QTest::qExec(test, argc, argv);
        }
    }
}
