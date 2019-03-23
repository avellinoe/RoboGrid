#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& FindStationState::robot() { return (Robot&) state_machine(); }

void FindStationState::entry(const Event& e) {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"ENTERED CLEAN STATE YOOOO"<<std::endl;
}

void FindStationState::during() {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"DURING CLEAN STATE LETS GOOO"<<std::endl;
    //do stuff here
    //update and refresh screen
}

void FindStationState::exit(const Event& e) {

    if (e.name() == "recharge") robot().goRecharge();   // Robot recharges at station
    else if (e.name() == "dead") robot().death();       // Robot battery is depleted
}