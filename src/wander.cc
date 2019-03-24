#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& WanderState::robot() { return (Robot&) state_machine(); }

void WanderState::entry(const Event& e) {

}

void WanderState::during() {
    
}

void WanderState::exit(const Event& e) {

    if (e.name() == "makenoise") robot().goMakeNoise();             // Robot begins to make noise
    else if (e.name() == "findstation") robot().goFindStation();    // Robot seeks out charge station
    else if (e.name() == "dead") robot().death();                   // Robot battery is depleted
    else if (e.name() == "off") robot().deactivateRobot();          // User deactivates Robot
}
