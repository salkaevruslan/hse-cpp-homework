#ifndef TEST_H
#define TEST_H

#include <cstddef>

#define DO_CHECK(expr) Test::check(expr,__FUNCTION__,__FILE__,__LINE__)

class Test {
public:

    static bool showFinalResult();

    virtual void runAllTests() = 0;

protected:
    static int failedNum;
    static int totalNum;

    static void check(bool expr, const char *func, const char *filename, size_t lineNum);
};

#endif

