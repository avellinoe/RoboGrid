#ifndef _ELMA_ROBOT_H
#define _ELMA_ROBOT_H

#include "elma/elma.h" // Note installation directory for elma

#include "on.h"
#include "off.h"
#include "wander.h"
#include "makenoise.h"
#include "evade.h"
#include "findstation.h"
#include "recharge.h"
#include "dead.h"
#include "robogrid.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;    

    //! A robot class, that inherits from StateMachine
    class Robot : public StateMachine {

        public:

            //! Construct Robot
            Robot();

            //! add event to list of events that have occurred
            void addEvent(string str);

            //! robot behavior
            void activateRobot();
            void deactivateRobot();
            void goWander();
            void goMakeNoise();
            void goEvade();
            void goFindStation();
            void goRecharge();
            void death();

            //! Status getters
            bool activated();
            bool wandering();
            bool makingnoise();
            bool evading();
            bool findingstation();
            bool recharging();
            bool isDead();

            high_resolution_clock::duration timeValue();

            
            //! Get a list of Events
            const vector<string>& addEvents() { return _currEvents; }

            //! Robot's battery and alarm. Battery decrements by 1 with each step,
            //! alarm is triggered when intercepting an intruder
            int _battery;
            bool _alarm;

        private:

            //! When overriding the StateMachine class, put state declarations here.
            OnState on;
            OffState off;
            WanderState wander;
            MakeNoiseState makenoise;
            EvadeState evade;
            FindStationState findstation;
            RechargeState recharge;
            DeadState dead;

            //! Boolean flag variables
            bool _activated = false;
            bool _wandering = false;
            bool _makingnoise = false;
            bool _evading = false;
            bool _findingstation = false;
            bool _recharging = false;
            bool _dead = false;
            
            //! Vector of events
            vector<string> _currEvents;
            
            //! Clock variables
            high_resolution_clock::time_point _start_time;
            high_resolution_clock::duration _elapsed;
    };
}
#endif