#include <iostream>
#include <chrono>
#include <vector>
#include <string>

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

    if (e.name() == "findstation") robot().goFindStation(); // Robot seeks out charge station
    else if (e.name() == "dead") robot().death();           // Robot battery is depleted
}