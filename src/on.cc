#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& OnState::robot() { return (Robot&) state_machine(); }

void OnState::exit(const Event& e) {

    switch (e.name()) {
        case "failsafe": robot().deactivateRobot(); break;  // User shuts down Robot
        case "wander": robot().goWander(); break;           // Robot starts to wander
    }
}
