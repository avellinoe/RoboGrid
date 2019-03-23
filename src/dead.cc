#include <iostream>
#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& DeadState::robot() { return (Robot&) state_machine(); }

void DeadState::entry(const Event& e) {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"ENTERED CLEAN STATE YOOOO"<<std::endl;
}

void DeadState::during() {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"DURING CLEAN STATE LETS GOOO"<<std::endl;
    //do stuff here
    //update and refresh screen
}

void DeadState::exit(const Event& e) {
    std::cout << std::endl;
    std::cout << "Robot battery is now depleted." << std::endl;
}