#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& RechargeState::robot() { return (Robot&) state_machine(); }

void RechargeState::entry(const Event& e) {

}

void RechargeState::during() {

}

void RechargeState::exit(const Event& e) {

    if (e.name() == "wander") robot().goWander();   // Robot resumes wandering
}