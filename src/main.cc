#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>
#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

int main() {

    Manager m;
    Robot robot;
    // RoboGrid earth(robot, "Users\\avellinoe\\Documents\\UW_EE_PMP\\Winter_2019\\EE590B\\RoboGrid\\src\\simulation.csv");
    RoboGrid earth(robot, "simulation.csv");

    m.schedule(earth, 10_ms)
     .schedule(robot, 10_ms)     
     .init()
     .run();

    endwin();
}