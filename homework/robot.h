#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

/*!
 * This is internally used by Robot, We won't be testing this class
 */
class RobotState : public State {
    public:
        RobotState(std::string name) : State(name) {}
        RobotState() : State() {}
        void entry(const Event& e){
            std::cout << "entering " + name() << "\n";
        }
        void during() {}
        void exit(const Event& e){}

    /*
     * Question 2: define a 'RobotState' that inherits from 'State'
     * Hint 1: you'll need to implement the 'virtual' methods and inherit both of
     * the 'State' constructors->
     */
  
};

class Robot : public StateMachine {

    public:

        Robot(std::string name) : StateMachine(name) {
            set_initial(Wander);
            add_transition("start", Idle, Wander);
            add_transition("found recharge station", FindRechargeStation, Recharge);
            add_transition("battery full", Recharge, Wander);
            add_transition("battery low", Wander, FindRechargeStation);
            add_transition("battery low", Evade, FindRechargeStation);
            add_transition("reset", MakeNoise, Wander);
            add_transition("reset", Evade, MakeNoise);
            add_transition("intruder detected", Wander, MakeNoise);
            add_transition("proximity warning", MakeNoise, Evade);
        }
        Robot() : StateMachine("Robot") {
            set_initial(Wander);
            add_transition("start", Idle, Wander);
            add_transition("found recharge station", FindRechargeStation, Recharge);
            add_transition("battery full", Recharge, Wander);
            add_transition("battery low", Wander, FindRechargeStation);
            add_transition("battery low", Evade, FindRechargeStation);
            add_transition("reset", MakeNoise, Wander);
            add_transition("reset", Evade, MakeNoise);
            add_transition("intruder detected", Wander, MakeNoise);
            add_transition("proximity warning", MakeNoise, Evade);
        }

        /*
        * Implement contructors-> Constructors should instantiate states
        * and transitions AND should set initial_state so that Event('start')
        * sets the Robot to state 'Wander'
        *
        * Look at code for StateMachine->h and in examples and elma/example if you need help->
        *
        * States should have the EXACT names:
        * "Recharge"
        * "Wander"
        * "Find Recharge Station"
        * "Evade"
        * "Make Noise"
        *
        * Robot should respond to events with the EXACT names:
        * "found recharge station"
        * "battery full"
        * "battery low"
        * "start"
        * "reset"
        * "intruder detected"
        * "proximity warning"
        */

    private:

        RobotState Idle = RobotState("Idle");
        RobotState Recharge = RobotState("Recharge");
        RobotState Wander = RobotState("Wander");
        RobotState FindRechargeStation = RobotState("Find Recharge Station");
        RobotState Evade = RobotState("Evade");;
        RobotState MakeNoise = RobotState("Make Noise");;
        /*
        * Hint: You may want to keep RobotState here since locally declared variables are destroyed
        */
};