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
    add_transition("wander", on, wander); // once initialized, robot is stationary until told to wander
    add_transition("makenoise", wander, makenoise); // when intruder is detected (same row or same column)
    add_transition("findstation", wander, findstation); // when battery reaches threshold
    add_transition("findstation", evade, findstation); // when battery reaches threshold
    add_transition("evade", makenoise, evade); // when intruder is close to robot
    add_transition("recharge", findstation, recharge); // when charge station is found
    add_transition("wander", recharge, wander); // when battery is full
    add_transition("dead", wander, dead); // when battery reaches zero
    add_transition("dead", makenoise, dead); // when battery reaches zero
    add_transition("dead", evade, dead); // when battery reaches zero
    add_transition("dead", findstation, dead); // when battery reaches zero
    add_transition("failsafe", on, off);
    add_transition("off", wander, off);

    _battery = 100; // Start with fully charged battery
    _alarm = false; // Start with alarm turned off
}

void Robot::addEvent(string str) {
    _currEvents.push_back(str);
}

void Robot::activateRobot() {
    _start_time = high_resolution_clock::now();
    _activated = true;
    string currE = "Robot activated";
    addEvent(currE);
}

void Robot::deactivateRobot() {
    _activated = false;
    _wandering = false;
    string currE = "Robot deactivated";
    addEvent(currE);
}

void Robot::goWander() {
    _wandering = true; // Note that wandering simply means that the Robot is able to move freely
    string currE = "Robot is wandering";
    addEvent(currE);
}

void Robot::goMakeNoise() {
    _makingnoise = true; // Robot is still activated and wandering
    string currE = "Robot is making noise";
    addEvent(currE);
}

void Robot::goEvade() {
    _evading = true; // Robot is still activated, wandering, and making noise
    string currE = "Robot is recharging";
    addEvent(currE);
}

void Robot::goFindStation() {
    _findingstation = true; // Robot is still activated and wandering
    _makingnoise = false;   // but Robot is no longer making noise
    _evading = false;       // nor is it evading
    string currE = "Robot is finding station";
    addEvent(currE);
}

void Robot::goRecharge() {
    _recharging = true; // Robot is still activated
    _wandering = false; // but no longer wandering
    string currE = "Robot is recharging";
    addEvent(currE);
}

void Robot::death() {
   _activated = false;
   _wandering = false;
   _dead = true;
   string currE = "Robot battery depleted";
   addEvent(currE);
}

high_resolution_clock::duration Robot::timeValue() {
    return high_resolution_clock::now() - _start_time;
}

bool Robot::activated() { return _activated; }
bool Robot::wandering() { return _wandering; }
bool Robot::makingnoise() { return _makingnoise; }
bool Robot::evading() { return _evading; }
bool Robot::findingstation() { return _findingstation; }
bool Robot::recharging() { return _recharging; }
bool Robot::isDead() { return _dead; }