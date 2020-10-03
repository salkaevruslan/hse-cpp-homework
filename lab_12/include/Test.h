#ifndef TEST_H
#define TEST_H

#include <cstddef>

#define DO_CHECK(expr) Test::check(expr,__FUNCTION__,__FILE__,__LINE__)

namespace test {

    class Test {
    public:

        static bool showFinalResult();

        virtual void run_tests() = 0;

    protected:
        static int failedNum;
        static int totalNum;

        static void check(bool expr, const char *func, const char *filename, size_t lineNum);
    };
}// test
#endif

