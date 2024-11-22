#include <gtest/gtest.h>
#include "threading/tasks/threading.h"

int r = 0;

void square(int i) {
    r = i*i;
}

TEST(Threading, PostTask) {
    auto th = threading::PostTask(square, 10);
    th->wait();

    EXPECT_EQ(r, 100);
}