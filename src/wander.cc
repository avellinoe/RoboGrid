#include <iostream>
#include <chrono>
#include <vector>
#include <string>

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

    if (e.name() == "makenoise") robot().goMakeNoise();             // Robot begins to make noise
    else if (e.name() == "findstation") robot().goFindStation();    // Robot seeks out charge station
    else if (e.name() == "dead") robot().death();                   // Robot battery is depleted
    else if (e.name() == "off") robot().deactivateRobot();          // User deactivates Robot
}
