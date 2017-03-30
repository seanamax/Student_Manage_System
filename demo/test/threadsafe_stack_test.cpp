//
// Created by Chris on 17/3/25.
//

#include "gtest/gtest.h"
#include "../threadsafe_stack.h"
#include <cstring>

using namespace std;
using namespace NaiNa;
TEST(threadsafe_stack_test, test_push_and_pop_function)
{
    threadsafe_stack<int> a;
    //EXPECT_EQ(1, 2);

    a.push(3);
    auto ptr= a.pop();
    EXPECT_EQ(*ptr, 3);

    int int_ = 4;
    a.push(int_);
    int_ = 5;
    a.pop(int_);
    EXPECT_EQ(int_, 4);


    // testing the empth stack.
    try {
        a.pop();
    }

    catch(exception e) {
        stack_empty ee;
        EXPECT_EQ(strcmp(e.what(), ee.what()), -1);
    }

    //EXPECT_EQ(2, 3);


    try {
        a.pop(int_);
    }

    catch(exception e) {
        stack_empty ee;
        EXPECT_EQ(strcmp(e.what(), ee.what()), -1);
    }
}


