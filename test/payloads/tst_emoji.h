#ifndef EMOJITEST_H
#define EMOJITEST_H

#include <testsuite.h>

class EmojiTest : public TestSuite
{
    Q_OBJECT
public:
    EmojiTest() {}
    ~EmojiTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // EMOJITEST_H
