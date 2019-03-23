#ifndef _ELMA_ROBOT_CLEAN_H
#define _ELMA_ROBOT_CLEAN_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot;  // Declare containing class so it can be refered to here
                      // before it is defined in stopwatch.h 

    //! The run state of the robot
    class CleanState : public State {        

        public:
        //! Build a new run state
        CleanState() : State("clean") {};
        void entry(const Event& e) ;
        void during();

        //! Perform actions required when switching from off to on
        //! \param e The event that triggered the transition        
        void exit(const Event&);

        Robot& robot();        

    };

}

#endif