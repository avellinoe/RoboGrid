#include "gtest/gtest.h"
#include "robot.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace elma;

double tolerance = 0.01;
/*!!
 * Here we use your StopWatch class to time something.
 */
TEST(Question1, StopWatch) {
    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();
    
    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    m.emit(Event("stop"));
    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    m.emit(Event("reset"));
    m.emit(Event("reset"));
    m.emit(Event("reset"));
    m.emit(Event("reset"));
    m.emit(Event("reset"));
    m.emit(Event("reset"));
    // m.emit(Event("smash")); // will fail with Elma error
    // EXPECT_NEAR(watch.seconds(), 0.0, tolerance);

    // m.emit(Event("start"));
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    // m.emit(Event("reset"));
    // EXPECT_NEAR(watch.seconds(), 0.0, tolerance);
}


/*!!
 * Here we use your Robot class to give the robot
 * a little trial and see what state its in.
 *
 * Variants of tests will include more than one robot,
 * non-sense events, and varying event sequences.
 */

TEST(Question2, RobotEnvironment1) {

    // create a new robot
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";

    /*
     * Send signals to robot and test
     */

    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery full"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

}

/*!!
 * Here we will create various StateMachines and validate the JSON from the to_json method.
 */
TEST(Question3, to_json) {
    /*
     * coming soon... but this is straight-forward to test. At this point, you shouldn't
     * need help writing tests for this one.
     */

    // create a new robot
    Robot robot = Robot("What a very nice robot");

    // init manager
    // Manager m;
    // m.schedule(robot, 10_ms)
    // .init()
    // .start()
    // .emit(Event("start"));

    std::cout << robot.to_json().dump(4) << std::endl;
}

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */
TEST(Question4, WatchPriority) {
    /*
     * coming soon...
     */
}