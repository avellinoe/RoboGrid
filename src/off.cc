#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& OffState:: robot() { return (Robot&) state_machine(); }

void OffState::exit(const Event& e) {
    if ( e.name() == "on" ) {
        // User turned on the robot
        robot().turnOn();
    }
}
