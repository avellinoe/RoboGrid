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
    UserInterface ui(robot);

    m.schedule(ui, 10_ms)
     .schedule(robot, 10_ms)     
     .init()
     .run();

    endwin();     
     
}