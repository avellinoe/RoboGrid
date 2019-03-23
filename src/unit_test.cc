#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "gtest/gtest.h"
#include "robot.h"

namespace {
 
    using namespace elma;
    using namespace robot;

    TEST(Robot,Construction) { 
        Robot robot; 
        ASSERT_EQ("off", robot.current().name());
    }

    // More tests go here. You should aim to test every
    // method of every object, either directly or indirectly,
    // although testing user interfaces is notoriously 
    // difficult.

}