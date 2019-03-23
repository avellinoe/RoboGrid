#ifndef _ELMA_ROBOT_H
#define _ELMA_ROBOT_H

#include "elma/elma.h" // Note installation directory for elma

#include "on.h"
#include "off.h"
#include "run.h"
#include "clean.h"
#include "robogrid.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;    

    //! A robot class, that inherits from StateMachine
    class Robot : public StateMachine {

        public:
        //! Make a new robot
        Robot();

        //! turn on the robot
        void turnOn();

        //! turn off the robot
        void turnOff();

        //! add event to list of events that have occured
        void addEvent(string str);

        //! robot runs
        void runner();
        void cleaner();
        bool isOn();
        bool isCleaning();
        high_resolution_clock::duration timeValue();
       //! Get a list of Events
       const vector<string>& addEvents() { return _currEvents; }

        private:

        // When overriding the StateMachine class, put state declarations here.
        OnState on;
        OffState off;
        RunState run;
        CleanState clean;

        // Other private variables
        bool _running;
        high_resolution_clock::time_point _start_time;
        high_resolution_clock::duration _elapsed;
        vector<string> _currEvents;
        bool _isOn = false;
        bool _isCleaning = false;

    };

}

#endif