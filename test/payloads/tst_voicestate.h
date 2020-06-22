#ifndef VOICESTATETEST_H
#define VOICESTATETEST_H

#include <QObject>
#include <testsuite.h>

class VoiceStateTest : public TestSuite
{
    Q_OBJECT
public:
    VoiceStateTest() {}
    ~VoiceStateTest() {}

private slots:
    void test_deserialization_full();
    void test_deserialization_minimal();
    void test_serialization_full();
    void test_serialization_minimal();
};

#endif // VOICESTATETEST_H
