#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& OffState::robot() { return (Robot&) state_machine(); }
void OffState::entry(const Event& e) {}
void OffState::during() {}
void OffState::exit(const Event& e) {

    if (e.name() == "on") robot().activateRobot();  // User activates Robot
}
