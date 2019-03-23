#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& CleanState:: robot() { return (Robot&) state_machine(); }

void CleanState::entry(const Event& e) {
    
        // User runs the robot
        //std::cout<<std::endl;
        //std::cout <<"ENTERED CLEAN STATE YOOOO"<<std::endl;
    
}

void CleanState::during() {
    
        // User runs the robot
        //std::cout<<std::endl;
        //std::cout <<"DURING CLEAN STATE LETS GOOO"<<std::endl;

        //do stuff here
        //update and refresh screen
    
}

void CleanState::exit(const Event& e) {
    if ( e.name() == "off" ) {
        // User runs the robot
        robot().turnOff();
    } 
}
