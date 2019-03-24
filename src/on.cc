#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& OnState::robot() { return (Robot&) state_machine(); }
void OnState::entry(const Event& e) {}
void OnState::during() {}
void OnState::exit(const Event& e) {
    
    if (e.name() == "failsafe") robot().deactivateRobot();  // User shuts down Robot
    else if (e.name() == "wander") robot().goWander();      // Robot starts to wander
}
