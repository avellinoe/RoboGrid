#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& MakeNoiseState::robot() { return (Robot&) state_machine(); }

void MakeNoiseState::entry(const Event& e) {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"ENTERED CLEAN STATE YOOOO"<<std::endl;
}

void MakeNoiseState::during() {
    // User runs the robot
    //std::cout<<std::endl;
    //std::cout <<"DURING CLEAN STATE LETS GOOO"<<std::endl;
    //do stuff here
    //update and refresh screen
}

void MakeNoiseState::exit(const Event& e) {
    
    if (e.name() == "evade") robot().goEvade();     // Robot begins to make noise
    else if (e.name() == "dead") robot().death();   // Robot battery is depleted
}
