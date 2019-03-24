#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot& DeadState::robot() { return (Robot&) state_machine(); }

void DeadState::entry(const Event& e) {

}

void DeadState::during() {

}

void DeadState::exit(const Event& e) {
    std::cout << std::endl;
    std::cout << "Robot battery is now depleted." << std::endl;
}