#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& WanderState::robot() { return (Robot&) state_machine(); }

void WanderState::entry(const Event& e) {
    // User runs the robot
    std::cout << std::endl;
    std::cout << "ENTERED STATE YOOOO"<<std::endl;
}

void WanderState::during() {
    // User runs the robot
    std::cout << std::endl;
    std::cout << "DURING STATE LETS GOOO"<<std::endl;
    //do stuff here
    //update and refresh screen
}

void WanderState::exit(const Event& e) {
    switch (e.name()) {
        case "makenoise": robot().goMakeNoise(); break;     // Robot begins to make noise
        case "findstation": robot().goFindStation(); break; // Robot seeks out charge station
        case "dead": robot().death(); break;                // Robot battery is depleted
        case "off": robot().deactivateRobot(); break;       // User deactivates Robot
    }
}
