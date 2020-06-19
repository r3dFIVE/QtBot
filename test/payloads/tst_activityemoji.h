#ifndef TST_EMOJI_H
#define TST_EMOJI_H

#include <testsuite.h>

class ActivityEmojiTest : public TestSuite
{
    Q_OBJECT
public:
    ActivityEmojiTest() {}
    ~ActivityEmojiTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // TST_EMOJI_H
