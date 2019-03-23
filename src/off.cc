#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& OffState::robot() { return (Robot&) state_machine(); }

void OffState::exit(const Event& e) {

    switch (e.name()) {
        case "on": robot().activateRobot(); break;  // User activates Robot
    }
}
