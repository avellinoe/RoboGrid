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

}

void FindStationState::during() {
    robot().goRecharge();
}

void FindStationState::exit(const Event& e) {

    if (e.name() == "dead") robot().death();       // Robot battery is depleted
}