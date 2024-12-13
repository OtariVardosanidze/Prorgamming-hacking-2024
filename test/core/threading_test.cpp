#include <gtest/gtest.h>
#include "threading/tasks/threading.h"


TEST(Threading, PostTask) {

    int r = 0;

    auto square = [&r](int i)->void {
        r = i*i;
    };

    auto th = threading::PostTask(square, 10);
    th->wait();

    EXPECT_EQ(r, 100);
}