#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& OnState:: robot() { return (Robot&) state_machine(); }

void OnState::exit(const Event& e) {
    if ( e.name() == "off" ) {
        // User turned off the robot
        robot().turnOff();
    }  else if ( e.name() == "run" ) {
        // User wants to run
        robot().runner();
    }else if ( e.name() == "clean" ) {
        // User wants to clean
        robot().cleaner();
    }
    
}
