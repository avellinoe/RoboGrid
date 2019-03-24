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

}

void EvadeState::during() {

}

void EvadeState::exit(const Event& e) {

    if (e.name() == "findstation") robot().goFindStation(); // Robot seeks out charge station
    else if (e.name() == "dead") robot().death();           // Robot battery is depleted
}