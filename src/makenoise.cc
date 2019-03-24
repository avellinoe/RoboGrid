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

}

void MakeNoiseState::during() {

}

void MakeNoiseState::exit(const Event& e) {

    if (e.name() == "evade") robot().goEvade();     // Robot begins to make noise
    else if (e.name() == "dead") robot().death();   // Robot battery is depleted
}
