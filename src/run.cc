#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& RunState:: robot() { return (Robot&) state_machine(); }

void RunState::entry(const Event& e) {
    
        // User runs the robot
        std::cout<<std::endl;
        std::cout <<"ENTERED STATE YOOOO"<<std::endl;
    
}

void RunState::during() {
    
        // User runs the robot
        std::cout<<std::endl;
        std::cout <<"DURING STATE LETS GOOO"<<std::endl;

        //do stuff here
        //update and refresh screen
    
}

void RunState::exit(const Event& e) {
    if ( e.name() == "off" ) {
        // User runs the robot
        robot().turnOff();
    } 
}
