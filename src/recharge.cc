#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& RechargeState::robot() { return (Robot&) state_machine(); }

void RechargeState::entry(const Event& e) {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"ENTERED CLEAN STATE YOOOO"<<std::endl;
}

void RechargeState::during() {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"DURING CLEAN STATE LETS GOOO"<<std::endl;
    //do stuff here
    //update and refresh screen
}

void RechargeState::exit(const Event& e) {
    switch (e.name()) {
        case "wander": robot().goWander(); break; // Robot resumes wandering
    }
}