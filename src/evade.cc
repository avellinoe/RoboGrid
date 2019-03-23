#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& EvadeState::robot() { return (Robot&) state_machine(); }

void EvadeState::entry(const Event& e) {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"ENTERED CLEAN STATE YOOOO"<<std::endl;
}

void EvadeState::during() {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"DURING CLEAN STATE LETS GOOO"<<std::endl;
    //do stuff here
    //update and refresh screen
}

void EvadeState::exit(const Event& e) {
    switch (e.name()) {
        case "findstation": robot().goFindStation(); break; // Robot seeks out charge station
        case "dead": robot().death(); break;                // Robot battery is depleted
    }
}