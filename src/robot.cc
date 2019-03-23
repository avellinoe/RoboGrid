#include <chrono>
#include <vector>

#include "robot.h"

using namespace std::chrono;
using namespace elma;
using namespace robot;

Robot::Robot() : StateMachine("robot") {

    // Define state machine initial states and transitions here
    set_initial(off);
    set_propagate(false);
    add_transition("on", off, on);
    add_transition("run", on, run);            
    add_transition("off", run, off);
    add_transition("off", on, off);
    add_transition("clean", run, clean);
    add_transition("run", clean, run);
    add_transition("off", clean, off);

    // Make sure we start in the right condition
    //reset();
}

void Robot::addEvent(string str) {
    _currEvents.push_back(str);
}



void Robot::turnOn() {
   // _start_time = high_resolution_clock::now();
   _isOn = true;
   string currE = "Robot turned on";
   addEvent(currE);
}

void Robot::turnOff() {
   // _elapsed = high_resolution_clock::duration::zero();
   // _laps.clear();
   _isOn = false;
   _isCleaning = false;
   string currE = "Robot turned off";
   addEvent(currE);
}


void Robot::runner() {
    //_elapsed += high_resolution_clock::now() - _start_time;
   string currE = "Robot is running around";
   _isCleaning = false;
   addEvent(currE);
}

void Robot::cleaner() {
    //_elapsed += high_resolution_clock::now() - _start_time;
    _start_time = high_resolution_clock::now();
    _isCleaning = true;
   string currE = "Robot is cleaning";
   addEvent(currE);
}

high_resolution_clock::duration Robot::timeValue() {
    return high_resolution_clock::now() - _start_time;
}

// Getters for UI
// bool Robot::flagStatus(){
//     return _pathFlag;
// }

bool Robot::isOn(){
    return _isOn;
}

bool Robot::isCleaning(){
    return _isCleaning;
}

// bool Robot::enemyStatus(){
//     return _enemy;
// }

// bool Robot::shieldStatus(){
//     return _shieldOn;
// }

// bool Robot::arrowStatus(){
//     return _arrowFired;
// }